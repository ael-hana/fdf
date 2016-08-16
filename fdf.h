/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:34:12 by ael-hana          #+#    #+#             */
/*   Updated: 2016/08/16 04:07:48 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDF_H__
# define __FDF_H__
# include "libft/libft.h"
# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "get_next_line/get_next_line.h"
# define WINDOW_X 1000
# define WINDOW_Y 500

typedef struct	s_env
{
	void		*mlx_ptr;
	void		*mlx_win;
	char		**map;
	char		***line;
	char		*tmp;
	char		*map_s;
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			z;
	int			rot;
	int			zoom;
	int			color;
	int			y_start;
	int			x_start;
	int			padding;
	void		*mlx;
	void		*win;
}				t_env;

typedef struct s_norm
{
	int			h;
	int			h2;
	int			x1;
	int			x2;
	int			y1;
	int			y2;

	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			err;
	int			e2;
}				t_norm;

void			ft_print_error(int opcode);
char			**ft_parse_map(t_env *ptr, char *file);
char			chech_line(char ***str);
int				ft_atoi_custom(char *str, char **nstr);
void			ft_split_nbr(t_env	*ptr);
void			trace_table(t_env *ptr);
void			ft_clear_window(t_env *ptr);
void			reset_val(t_env *ptr);
void			ft_next_exit_prog(int keycode, t_env *ptr);
int				ft_exit_prog(int keycode, t_env *ptr);
void			call_sys(t_env	*ptr, int i, int x, int opcode);
void			ft_init_pos(int x1, int x2, t_env *ptr);
void			display_menu(t_env *ptr);
void			ft_brase_zebi(t_env *ptr, t_norm *x);
#endif
