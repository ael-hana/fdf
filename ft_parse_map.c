/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:43:21 by ael-hana          #+#    #+#             */
/*   Updated: 2016/08/17 22:10:04 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_split_nbr(t_env *ptr)
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
		while (str[0][y])
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
	tmp = ptr->map_s;
	ptr->map_s = ft_strjoin(tmp, "\n");
	free(tmp);
	return (ft_strsplit(ptr->map_s, '\n'));
}

void		ft_init_pos(int x1, int x2, t_env *ptr)
{
	ptr->x1 = x1;
	ptr->x2 = x2;
}

void		display_menu(t_env *ptr)
{
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,
			WINDOW_Y / 36, ptr->color, "ECHAP : exit");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,
			WINDOW_Y / 18, ptr->color, "R : reset");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,
			WINDOW_Y / 12, ptr->color, "<- -> w s : x - y");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,
			WINDOW_Y / 8, ptr->color, "HAUT BAS : ZOOM");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,
			WINDOW_Y / 6, ptr->color, "+ ou - : Z");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,
			WINDOW_Y / 5, ptr->color, ", . : rotation");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,
			WINDOW_Y / 4, ptr->color, "C : color");
}
