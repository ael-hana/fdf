/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:33:30 by ael-hana          #+#    #+#             */
/*   Updated: 2016/08/15 09:49:13 by ael-hana         ###   ########.fr       */
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
	else if (opcode == 4)
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

void		call_sys(t_env	*ptr, int h, int h2, int x1, int x2, int y1, int y2, int opt)
{
	if (opt)
		ft_brase_zebi(ptr, (x1 - y1) * (ptr->padding),
			(x2 - y2) * (ptr->padding),
			((y1 + x1) * (ptr->padding / 2)) - h * 4,
			((y2 + x2) * (ptr->padding / 2)) - h2 * 4);
	else
		ft_brase_zebi(ptr, (x1 - y1) * (ptr->padding),
			(x1 - (y1 + ptr->padding * 2)) * (ptr->padding),
			(((y1 + x1)) * (ptr->padding / 2)) - h * 4,
			((y2 + x2 + ptr->padding)) * (ptr->padding / 2) - h2 * 4);
}

void	trace_table(t_env *ptr)
{
	int		i;
	int		x;
	char	**tmp;

	ptr->x1 = 50;
	ptr->y1 = 0;
	ptr->x2 = 50 + ptr->padding;
	ptr->y2 = 0;
	i = 0;
	while ((tmp = ptr->line[i]))
	{
		x = 0;
		while (tmp[x + 1])
		{
			call_sys(ptr, ft_atoi(tmp[x]), ft_atoi(tmp[x + 1]), ptr->x1, ptr->x2, ptr->y1, ptr->y2, 1);
			if (ptr->line[i + 1])
				call_sys(ptr, ft_atoi(tmp[x]), ft_atoi(ptr->line[i + 1][x]), ptr->x1, ptr->x2, ptr->y1, ptr->y2, 0);
				//ft_brase_zebi(ptr, ptr->x1, ptr->x1, ptr->y1, ptr->y2 + ptr->padding);
			ptr->x1 = ptr->x2;
			ptr->x2 += ptr->padding;
			++x;
		}
		if (ptr->line[i + 1] && tmp[x])
				call_sys(ptr, ft_atoi(tmp[x]), ft_atoi(ptr->line[i + 1][x]), ptr->x1, ptr->x2, ptr->y1, ptr->y2, 0);
		else
		{
			ptr->y1 += ptr->padding;
			ptr->y2 += ptr->padding;
			ptr->x1 = 50;
			ptr->x2 = 50 + ptr->padding;
			x = 0;
			tmp = ptr->line[i];
			while (tmp[x + 1])
			{
				call_sys(ptr, ft_atoi(tmp[x]), ft_atoi(tmp[x + 1]), ptr->x1, ptr->x2, ptr->y1, ptr->y2, 1);
					ptr->x1 = ptr->x2;
					ptr->x2 += ptr->padding;
				++x;
			}
		}
			//ft_brase_zebi(ptr, ptr->x1, ptr->x1, ptr->y1, ptr->y2 + ptr->padding);
		ptr->y1 += ptr->padding;
		ptr->y2 += ptr->padding;
		ptr->x1 = 50;
		ptr->x2 = 50 + ptr->padding;
		++i;
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
	ptr->padding = 4;
	if (!(ptr->map = ft_parse_map(ptr, av[1])))
		ft_print_error(0);
	ft_split_nbr(ptr);
	if (chech_line(ptr->line))
		ft_print_error(2);
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 2000, 1600, "FDF");
	trace_table(ptr);
	mlx_loop(ptr->mlx);
	return (0);
}
