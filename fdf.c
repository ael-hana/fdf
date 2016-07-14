/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:33:30 by ael-hana          #+#    #+#             */
/*   Updated: 2016/07/14 19:47:49 by ael-hana         ###   ########.fr       */
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
	exit(EXIT_FAILURE);
}

void	ft_brase_zebi(t_env * ptr)
{
	int		dx;
	int		sx;
	int		dy;
	int		sy;
 	int		err;
	int		e2;

	dx = (ptr->x2 - ptr->x1);
	if (dx < 0)
	{
		dx *= -1;
		sx = -1;
	}
	else
		sx = 1;
	dy = (ptr->y2 - ptr->y1);
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
		mlx_pixel_put(ptr->mlx, ptr->win, ptr->x1, ptr->y1, 0x00FFFFFF);
		if (ptr->x1 == ptr->x2 && ptr->y1 == ptr->y2)
			return;
		e2 = err;
		if (e2 >-dx)
		{
			err -= dy;
			ptr->x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			ptr->y1 += sy;
		}
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
	if (!(ptr->map = ft_parse_map(ptr, av[1])))
		ft_print_error(0);
	if (chech_line(ptr->map))
		ft_print_error(2);
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, 800, 600, "FDF");
	ptr->x1 = 0;
	ptr->y1 = 0;
	ptr->x2 = 799;
	ptr->y2 = 599;
	ft_brase_zebi(ptr);
	mlx_loop(ptr->mlx);
	return (0);
}
