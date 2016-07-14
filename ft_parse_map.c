/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:43:21 by ael-hana          #+#    #+#             */
/*   Updated: 2016/07/14 18:34:15 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			nb_space(char *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		if (*str == ' ')
			++i;
		++str;
	}
	return (i);
}

char		chech_line(char **str)
{
	int	i;
	int	nb;

	i = 1;
	nb = nb_space(str[0]);
	if (!nb)
		return (0);
	while (str[i])
	{
		if (nb != nb_space(str[i]))
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
