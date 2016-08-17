/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:34:12 by ael-hana          #+#    #+#             */
/*   Updated: 2016/08/17 22:16:50 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
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

typedef struct	s_norm
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
void			*mlx_init();
int				mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param);
int				mlx_loop (void *mlx_ptr);
void			*mlx_new_window(void *mlx_ptr, int size_x, int size_y,
				char *title);
int				mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y,
				int color);
int				mlx_string_put(void *mlx_ptr, void *win_ptr, int x,
				int y, int color, char *string);
#endif
