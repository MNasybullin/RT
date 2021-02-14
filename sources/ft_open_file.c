/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:27:19 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/14 14:09:50 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <sys/stat.h>

int				ft_check_file(const char *file, unsigned check)
{
	struct stat st;
	int			ret;

	if (!file || stat(file, &st) == -1)
		return (-1);
	ret = 1;
	if (check & IS_D)
		ret &= S_ISDIR(st.st_mode);
	if (check & IS_R)
		ret &= ((st.st_mode & S_IRUSR) != 0);
	if (check & IS_W)
		ret &= ((st.st_mode & S_IWUSR) != 0);
	if (check & IS_X)
		ret &= ((st.st_mode & S_IXUSR) != 0);
	return (ret);
}

int				ft_open_file(const char *path)
{
	int			ret;
	int			error;

	error = 0;
	if (ft_check_file(path, IS_E) <= 0)
		error += write(2, "RT: no such file - ", 19);
	else if ((ret = open(path, O_RDONLY)) < 0)
		error += write(2, "RT: can't open that file - ", 27);
	else if (!ft_check_file(path, IS_R))
		error += write(2, "RT: can't read from that file - ", 32);
	else if (ft_check_file(path, IS_D))
		error += write(2, "RT: it's a directory - ", 23);
	if (error)
	{
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
