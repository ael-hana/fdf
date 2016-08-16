/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:43:21 by ael-hana          #+#    #+#             */
/*   Updated: 2016/08/16 02:18:58 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_atoi_custom(char *str, char **nstr)
{
	int		n;

	while (*str == ' ')
		++str;
	n = 0;
	if (*str == '-')
	{
		while (++str && *str && *str != ' ')
		{
			if (*str < '0' || *str > '9')
				ft_print_error(3);
			n += *str - '0';
		}
		while (*str == ' ')
			*nstr = ++str;
		return (n * -1);
	}
	while (*str && *str != ' ')
	{
		if (*str < '0' || *str > '9')
			ft_print_error(3);
		n += *str++ - '0';
	}
	while (*str == ' ')
		*nstr = ++str;
	return (n);
}

void		ft_split_nbr(t_env	*ptr)
{
	int		i;

	i = 0;
	while (ptr->map[i])
		++i;
	if (!(ptr->line = malloc(sizeof(char ***) * (i + 1))))
		ft_print_error(4);
	ptr->line[i] = NULL;
	i = 0;
	while (ptr->map[i])
	{
		ptr->line[i] = ft_strsplit(ptr->map[i], ' ');
		++i;
	}
}

char		chech_line(char ***str)
{
	int		i;
	int		y;
	int		res;

	if (str[0])
	{
		y = 0;
		while(str[0][y])
			res = ++y;
	}
	i = 1;
	while (str[i])
	{
		y = 0;
		while (str[i][y])
			 ++y;
		if (res != y)
			return (-1);
		++i;
	}
	return (0);
}

char		**ft_parse_map(t_env *ptr, char *file)
{
	int		fd;
	void	*tmp;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_print_error(1);
	ptr->map_s = NULL;
	ptr->tmp = NULL;
	get_next_line(fd, &ptr->map_s);
	while (get_next_line(fd, &ptr->tmp) > 0)
	{
		tmp = ptr->tmp;
		ptr->tmp = ft_strjoin("\n", ptr->tmp);
		free(tmp);
		tmp = ft_strjoin(ptr->map_s, ptr->tmp);
		free(ptr->tmp);
		free(ptr->map_s);
		ptr->map_s = tmp;
	}
	ptr->map_s = ft_strjoin(tmp = ptr->map_s, "\n");
	free(tmp);
	return (ft_strsplit(ptr->map_s, '\n'));
}
