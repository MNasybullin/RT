/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 23:25:05 by mgalt             #+#    #+#             */
/*   Updated: 2020/11/26 19:10:57 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"
#include "libft.h"

int		err_invalid_file(void)
{
    ft_putendl("Error: file is invalid");
    return (-1);
}

int		err_trans_matrix(void)
{
    ft_putendl("Error: tranformation matrix is invalid");
    return (-1);
}

int		err_wrong_format(void)
{
    ft_putendl("Error: wrong data format");
    return (-1);
}

int		err_mem_alloc(void)
{
    ft_putendl("Error: memory allocation failed");
    return (-1);
}