/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:34:12 by ael-hana          #+#    #+#             */
/*   Updated: 2016/07/13 22:38:18 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDF_H__
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"

typedef struct	s_env
{
	void		*mlx_ptr;
	void		*mlx_win;
	char		**map;
	char		*tmp;
}				t_env;
#endif
