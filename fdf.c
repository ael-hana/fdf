/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:33:30 by ael-hana          #+#    #+#             */
/*   Updated: 2016/07/17 21:26:20 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_print_error(int opcode)
{
	if (!opcode)
		ft_putstr_fd("Probleme malloc\n", 2);
	else if (opcode == 1)
		ft_putstr_fd("Impossible d'ouvrire le fichier\n", 2);
	else if (opcode == 2)
		ft_putstr_fd("PARSSING ERRROR\n", 2);
	else if (opcode == 3)
		ft_putstr_fd("MAP ERROR\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_brase_zebi(t_env * ptr, int x1, int x2, int y1, int y2)
{
	int		dx;
	int		sx;
	int		dy;
	int		sy;
 	int		err;
	int		e2;

	dx = (x2 - x1);
	if (dx < 0)
	{
		dx *= -1;
		sx = -1;
	}
	else
		sx = 1;
	dy = (y2 - y1);
	if (dy < 0)
	{
		dy *= -1;
		sy = -1;
	}
	else
		sy = 1;
	err = (dx>dy ? dx : -dy)/2;
	while (42)
	{
		mlx_pixel_put(ptr->mlx, ptr->win, x1, y1, 0x00FFFFFF);
		if (x1 == x2 && y1 == y2)
			return;
		e2 = err;
		if (e2 >-dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	trace_table(t_env *ptr)
{
	int		i;
	int		x;
	char	**tmp;
	int		s;

	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 800, 600, "FDF");
	ptr->x1 = 400;
	ptr->y1 = 0;
	ptr->x2 = 400 + ptr->padding;
	ptr->y2 = DESC;
	i = 0;
	x = 0;
	s = DESC;
	while (ptr->map[i])
	{
		if (ptr->map[i][0])
			tmp = ft_strsplit(ptr->map[i], ' ');
		else if (ptr->map[i + 1])
		{
			//ft_brase_zebi(ptr, ptr->x1, ptr->x2 - ptr->padding, ptr->y1, ptr->y2 + ptr->padding);
			ptr->y1 = (s * 2);
			ptr->y2 = (s * 2) + DESC;
			ptr->x1 = 400 + (-35 * ++i);
			ptr->x2 = 400 +  ptr->padding + (-35 * i);
			s += DESC;
		}
		else
			return ;
		ptr->z = ft_atoi_custom(ptr->map[i], &ptr->map[i]);
		ft_brase_zebi(ptr, ptr->x1, ptr->x2, ptr->y1 - ptr->z, ptr->y2 - ptr->z);
		printf("i : %d  x1 : %d x2 : %d y1 : %d y2 : %d\n", i, ptr->x1, ptr->x2, ptr->y1, ptr->y2);
		ptr->y1 = ptr->y2;
		ptr->y2 += DESC;
		//if (ptr->map[i + 1])
			//ft_brase_zebi(ptr, ptr->x1, ptr->x2 - ptr->padding, ptr->y1, ptr->y2 + ptr->padding);
		//printf("-> i : %d x1 : %d x2 : %d y1 : %d y2 : %d\n", i, ptr->x1, ptr->x2 - ptr->padding, ptr->y1, ptr->y2 + ptr->padding);
		ptr->x1 += ptr->padding;
		ptr->x2 += ptr->padding;
	}
}

int		main(int ac, char **av)
{
	t_env	*ptr;

	if (ac != 2)
	{
		ft_putstr_fd("Erreur de parametre\n", 2);
		return (-1);
	}
	if (!(ptr = malloc(sizeof(t_env))))
		ft_print_error(0);
	ptr->padding = 32;
	if (!(ptr->map = ft_parse_map(ptr, av[1])))
		ft_print_error(0);
	if (chech_line(ptr->map))
		ft_print_error(2);
	trace_table(ptr);
	mlx_loop(ptr->mlx);
	return (0);
}
