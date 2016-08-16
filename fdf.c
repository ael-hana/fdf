/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:33:30 by ael-hana          #+#    #+#             */
/*   Updated: 2016/08/16 19:58:00 by ael-hana         ###   ########.fr       */
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
	else if (opcode == 5)
		ft_putstr_fd("BYE BYE :)\n", 1);
	else if (opcode == 7)
		ft_putstr_fd("Erreur de parametre\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_brase_zebi(t_env *ptr, t_norm *x)
{
	x->dx = (x->x2 - x->x1);
	if (x->dx < 0)
	{
		x->dx *= -1;
		x->sx = -1;
	}
	else
		x->sx = 1;
	x->dy = (x->y2 - x->y1);
	if (x->dy < 0)
	{
		x->dy *= -1;
		x->sy = -1;
	}
	else
		x->sy = 1;
	x->err = (x->dx > x->dy ? x->dx : -x->dy) / 2;
	while (42)
	{
		mlx_pixel_put(ptr->mlx, ptr->win, x->x1, x->y1, ptr->color);
		if (x->x1 == x->x2 && x->y1 == x->y2)
			return;
		x->e2 = x->err;
		if (x->e2 > -x->dx)
		{
			x->err -= x->dy;
			x->x1 += x->sx;
		}
		if (x->e2 < x->dy)
		{
			x->err += x->dx;
			x->y1 += x->sy;
		}
	}
}

void		call_sys(t_env	*ptr, int i, int x, int opcode)
{
	t_norm c;

	if (!opcode)
	{
		c.h = ft_atoi(ptr->line[i][x]);
		c.h2 = ft_atoi(ptr->line[i][x + 1]);
	}
	else if(opcode == 1)
	{
		c.h = ft_atoi(ptr->line[i][x]);
		c.h2 = ft_atoi(ptr->line[i + 1][x ]);
	}
	else
	{
		c.h = ft_atoi(ptr->line[i - 1][x]);
		c.h2 = ft_atoi(ptr->line[i][x]);
	}
	c.x1 = (ptr->x1 - ptr->y1) * ptr->padding;
	c.y1 = (ptr->y1 + ptr->x1) * (ptr->padding / ptr->rot) - (c.h * ptr->zoom);
	c.x2 = (opcode ? ptr->x1 - (ptr->y1 + ptr->padding) : ptr->x2 - ptr->y2) *
		ptr->padding;
	c.y2 = (opcode ? (ptr->y1 + ptr->padding + ptr->x1) : (ptr->y2 + ptr->x2)) *
		(ptr->padding / ptr->rot) - (c.h2 * ptr->zoom);
	ft_brase_zebi(ptr, &c);
}

void	ft_init_pos(int x1, int x2, t_env *ptr)
{
	ptr->x1 = x1;
	ptr->x2 = x2;
}

void	display_menu(t_env *ptr)
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

int		main(int ac, char **av)
{
	t_env	*ptr;

	if (ac != 2)
		ft_print_error(7);
	if (!(ptr = malloc(sizeof(t_env))))
		ft_print_error(0);
	ptr->padding = 4;
	ptr->zoom = 3;
	ptr->rot = 2;
	ptr->y_start = 0;
	ptr->color = 0x00FFFFFF;
	ptr->x_start = 75;
	if (!(ptr->map = ft_parse_map(ptr, av[1])))
		ft_print_error(0);
	ft_split_nbr(ptr);
	if (chech_line(ptr->line))
		ft_print_error(2);
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, WINDOW_X, WINDOW_Y, "FDF");
	trace_table(ptr);
	mlx_key_hook(ptr->win, ft_exit_prog, ptr);
	mlx_loop(ptr->mlx);
	return (0);
}
