#include "../include/rt.h"
# define BUFF_SIZE		8
# define ENDL			'\n'
# define MAX_LONG_LONG 9223372036854775807
typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

char		*ft_strndup(const char *s1, size_t n);
void    	ft_putendl(char const *s);

void		ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*new;

	i = 0;
	new = (char *)s;
	while (n > i)
	{
		new[i] = '\0';
		i++;
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void				*ft_memcpy(void *dest, const void *source, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)dest;
	str2 = (unsigned char *)source;
	if (!source && !dest)
		return (NULL);
	i = 0;
	if (n <= 0)
		return (str1);
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (dest);
}

void		*ft_memalloc(size_t size)
{
	void	*new;

	if (size == 0)
		return (NULL);
	new = malloc(size);
	if (!new)
		return (NULL);
	ft_bzero(new, size);
	return (new);
}


char		*ft_strnew(size_t size)
{
	char	*new;

	if ((size + 1) < size)
		return (NULL);
	if (!(new = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(new, size + 1);
	return (new);
}


void	ft_putendl(char const *s)
{
	while (!s)
		return ;
	while (*s)
	{
		ft_putchar(*s);
		s++;
	}
	ft_putchar('\n');
}

int					ft_strcmp(const char *str1, const char *str2)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s2 == '\0' && *s1)
		return (1);
	else
		return (*s1 - *s2);
}

size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

static	int	ft_words(char const *s, char c)
{
	int		cu;
	int		i;

	i = 0;
	cu = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			cu++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (cu);
}

static	int	ft_len(char const *s, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

void	ft_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(*list))))
		return (NULL);
	if (!content)
	{
		list->content = NULL;
		list->content_size = 0;
	}
	else
	{
		if (!(list->content = malloc(content_size)))
			return (NULL);
		ft_memcpy(list->content, content, content_size);
		list->content_size = content_size;
	}
	list->next = NULL;
	return (list);
}


char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		l;

	if (!s)
		return (NULL);
	if (!(str = (char **)ft_memalloc(sizeof(char **) * (ft_words(s, c) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ft_words(s, c))
	{
		l = 0;
		if (!(str[i] = ft_strnew(ft_len(&s[j], c) + 1)))
			return (NULL);
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
			str[i][l++] = s[j++];
		str[i][l] = '\0';
	}
	str[i] = 0;
	return (str);
}

int			line_copy(char **line, char *content, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *line;
	while (content[i] && content[i] != c)
		i++;
	if (!(*line = ft_strndup(content, i)))
		return (0);
	return (i);
}

t_list		*get_live(int fd, t_list **hist)
{
	t_list	*tmp;

	if (!hist)
		return (NULL);
	tmp = *hist;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", fd);
	ft_lstadd(hist, tmp);
	return (tmp);
}

char		*ft_strndup(const char *s1, size_t n)
{
	char	*s2;
	size_t	i;

	i = 0;
	if (!(s2 = ft_strnew(n)))
		return (NULL);
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

char				*ft_strchr(const char *str, int ch)
{
	unsigned char	k;
	char			*new;

	k = (unsigned char)ch;
	new = (char *)str;
	while (*new)
	{
		if (*new == ch)
			return (new);
		else
			new++;
	}
	if (k == '\0')
		return (new);
	else
		return (NULL);
}


char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(new = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

int								ft_atoi(const char *str)
{
	static unsigned long		i;
	unsigned long long			num;
	static int					mod;

	i = 0;
	num = 0;
	if (!str)
		return (0);
	while (*(str + i) == '\n' || *(str + i) == '\t'  \
	|| *(str + i) == '\r' || *(str + i) == '\v' \
	|| *(str + i) == '\f' || *(str + i) == ' ')
		i++;
	mod = (*(str + i) == '-') ? -1 : 1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	while (*(str + i) && *(str + i) >= '0' && *(str + i) <= '9')
	{
		num = (unsigned long long)(num * 10 + (*(str + i++) - '0'));
		if (num > (long long)MAX_LONG_LONG && mod == 1)
			return (-1);
		if (num > (long long)MAX_LONG_LONG && mod == -1)
			return (0);
	}
	return ((int)(num * mod));
}
char	*ft_strdup(const char *src)
{
	int		i;
	char	*c;

	i = 0;
	if (!(c = (char *)malloc(ft_strlen(src) + 1)) \
	|| ft_strlen(src) > (ft_strlen(src) + 1))
		return (NULL);
	i = 0;
	while (src[i])
	{
		c[i] = src[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}


int			my_read(const int fd, char **content)
{
	int		read_result;
	char	*tmp;
	char	buf[BUFF_SIZE + 1];

	while ((read_result = read(fd, buf, BUFF_SIZE)))
	{
		buf[read_result] = '\0';
		tmp = *content;
		if (!(*content = ft_strjoin(*content, buf)))
			return (-1);
		free(tmp);
		if (ft_strchr(buf, ENDL))
			break ;
	}
	return (read_result);
}

int			get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	size_t			read_result;
	static t_list	*hist;
	t_list			*live;
	char			*tmp;

	if (fd < 0 || !line || (read(fd, buf, 0)) < 0 ||
		(!(live = get_live(fd, &hist))))
		return (-1);
	tmp = live->content;
	read_result = my_read(fd, &tmp);
	live->content = tmp;
	if (!read_result && !*tmp)
		return (0);
	read_result = line_copy(line, live->content, ENDL);
	tmp = live->content;
	if (tmp[read_result] != '\0')
	{
		live->content = ft_strdup(&((live->content)[read_result + 1]));
		free(tmp);
	}
	else
		tmp[0] = '\0';
	return (1);
}


void	check_tab_len(char **tab)
{
	if (len_tab(tab) != 2)
	{
		free_tab(tab);
		//error_output(INVALID);
		exit(-1);
	}
}

double	ft_strtodbl(char *s)
{
	char		**tab;
	double	x;
	double y;
	int			i;
	int			len;
	int			dot;

	x = 0.0;
	i = -1;
	y = 0;
	dot = 0;
	while (s[++i] != '\0')
		if (s[i] == '.')
			dot++;
	if (!dot)
		return ((double)ft_atoi(s));
	tab = ft_strsplit(s, '.');
	check_tab_len(tab);
	x = (double)ft_atoi(tab[0]);
	y = (double)ft_atoi(tab[1]);
	len = ft_strlen(tab[1]);
	while (--len > -1)
		y /= 10;
	if (s[0] == '-')
        x -= y;
    else
	    x += y;
	free_tab(tab);
	return (x);
}

int			ft_strequ(char const *s1, char const *s2)
{
	char	*new1;
	char	*new2;

	if (s1 && s2)
	{
		new1 = (char *)s1;
		new2 = (char *)s2;
		if (ft_strcmp(new1, new2) == 0)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}
