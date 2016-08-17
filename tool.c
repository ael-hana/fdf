/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 02:32:09 by ael-hana          #+#    #+#             */
/*   Updated: 2016/08/17 22:16:50 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		trace_table(t_env *ptr)
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
			call_sys(ptr, i, x, 0);
			if (ptr->line[i + 1])
				call_sys(ptr, i, x, 1);
			x++;
			ft_init_pos(ptr->x2, ptr->x2 + ptr->padding, ptr);
		}
		if (ptr->line[++i])
			call_sys(ptr, i, x, 2);
		ptr->y1 += ptr->padding;
		ptr->y2 += ptr->padding;
		ft_init_pos(ptr->x_start, ptr->x_start + ptr->padding, ptr);
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

void		reset_val(t_env *ptr)
{
	ptr->padding = 4;
	ptr->zoom = 3;
	ptr->rot = 2;
	ptr->y_start = 0;
	ptr->color = 0x00FFFFFF;
	ptr->x_start = 75;
}

void		ft_next_exit_prog(int keycode, t_env *ptr)
{
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
}

int			ft_exit_prog(int keycode, t_env *ptr)
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
	ft_next_exit_prog(keycode, ptr);
	return (0);
}
