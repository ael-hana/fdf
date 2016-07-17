/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:34:12 by ael-hana          #+#    #+#             */
/*   Updated: 2016/07/17 18:43:54 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDF_H__
# define __FDF_H__
# include "libft/libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "get_next_line/get_next_line.h"
# define DESC 15

typedef struct	s_env
{
	void		*mlx_ptr;
	void		*mlx_win;
	char		**map;
	char		*tmp;
	char		*map_s;
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			z;
	int			padding;
	void		*mlx;
	void		*win;
}				t_env;
void			ft_print_error(int opcode);
char			**ft_parse_map(t_env *ptr, char *file);
char			chech_line(char **str);
int				ft_atoi_custom(char *str, char **nstr);
#endif
