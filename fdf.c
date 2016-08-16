/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:33:30 by ael-hana          #+#    #+#             */
/*   Updated: 2016/08/16 02:18:56 by ael-hana         ###   ########.fr       */
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
	else if(opcode == 7)
		ft_putstr_fd("Erreur de parametre\n", 2);
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
		mlx_pixel_put(ptr->mlx, ptr->win, x1, y1, ptr->color);
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

void		call_sys(t_env	*ptr, int h, int h2, int x1, int x2, int y1, int y2)
{
	ft_brase_zebi(ptr, (x1 - y1) * (ptr->padding),
		(x2 - y2) * (ptr->padding),
		((y1 + x1) * (ptr->padding/ptr->rot)) - (h*ptr->zoom),
		((y2 + x2) * (ptr->padding/ptr->rot)) - (h2*ptr->zoom));
}

void	ft_init_pos(int x1, int x2, t_env *ptr)
{
	ptr->x1 = x1;
	ptr->x2 = x2;
}

void	display_menu(t_env *ptr)
{
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,  WINDOW_Y / 36, ptr->color, "ECHAP : exit");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,  WINDOW_Y / 18, ptr->color, "R : reset");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,  WINDOW_Y / 12, ptr->color, "<- -> w s : x - y");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,  WINDOW_Y / 8, ptr->color, "HAUT BAS : ZOOM");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,  WINDOW_Y / 6, ptr->color, "+ ou - : Z");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,  WINDOW_Y / 5, ptr->color, ", . : rotation");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300,  WINDOW_Y / 4, ptr->color, "C : color");
}
void	trace_table(t_env *ptr)
{
	int		i;
	int		x;

	ptr->y1 = ptr->y_start;
	ptr->y2 = ptr->y_start;
	i = 0;
	ft_init_pos(ptr->x_start, ptr->x_start + ptr->padding, ptr);
	display_menu(ptr);
	while (ptr->line[i])
	{
		x = 0;
		while (ptr->line[i][x + 1])
		{
			call_sys(ptr, atoi(ptr->line[i][x]), atoi(ptr->line[i][x + 1]), ptr->x1, ptr->x2, ptr->y1, ptr->y2);
			if (ptr->line[i + 1])
				call_sys(ptr, atoi(ptr->line[i][x]), atoi(ptr->line[i + 1][x]), ptr->x1, ptr->x1, ptr->y1, ptr->y1 + ptr->padding);
			x++;
			ft_init_pos(ptr->x2, ptr->x2 + ptr->padding, ptr);
		}
		if (ptr->line[i + 1])
				call_sys(ptr, atoi(ptr->line[i][x]), atoi(ptr->line[i + 1][x]), ptr->x1, ptr->x1, ptr->y1, ptr->y1 + ptr->padding);
		ptr->y1 += ptr->padding;
		ptr->y2 += ptr->padding;
		ft_init_pos(ptr->x_start, ptr->x_start + ptr->padding, ptr);
		++i;
	}
}

void		ft_clear_window(t_env *ptr)
{
	int		x;
	int		y;

	y = 0;
	while (y < WINDOW_Y)
	{
		x = 0;
		while (x < WINDOW_X)
		{
			mlx_pixel_put(ptr->mlx, ptr->win, x, y, 0);
			++x;
		}
		++y;
	}
}

void	reset_val(t_env *ptr)
{
	ptr->padding = 4;
	ptr->zoom = 3;
	ptr->rot = 2;
	ptr->y_start = 0;
	ptr->color = 0x00FFFFFF;
	ptr->x_start = 75;
}

int		ft_exit_prog(int keycode, t_env *ptr)
{
	if (keycode == 53)
		ft_print_error(5);
	ft_clear_window(ptr);
	if (keycode == 69)
		ptr->zoom++;
	if (keycode == 78)
		ptr->zoom--;
	if (keycode == 125)
		ptr->padding--;
	if (keycode == 126)
		ptr->padding++;
	if (keycode == 123)
		ptr->x_start--;
	if (keycode == 124)
		ptr->x_start++;
	if (keycode == 13)
		ptr->y_start++;
	if (keycode == 1)
		ptr->y_start--;
	if (keycode == 8)
		ptr->color = ptr->color == 0x00FFFFFF ? 0x0000FF00 : 0x00FFFFFF;
	if (keycode == 43)
		ptr->rot += ptr->rot == -1 ? 2 : 1;
	if (keycode == 47)
		ptr->rot += ptr->rot == 1 ? -2 : -1;
	if (keycode == 15)
		reset_val(ptr);
	trace_table(ptr);
	return (0);
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
