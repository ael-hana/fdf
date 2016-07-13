/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 21:43:21 by ael-hana          #+#    #+#             */
/*   Updated: 2016/07/13 22:38:16 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char		chech_line(char **str)
{
	while ()
}

void		*ft_parse_map(char *file)
{
	t_env	*ptr;
	int		fd;
	int		i;

	if (!(ptr = malloc(sizeof(t_env))))
	{
		ft_putstr_fd("Probleme malloc\n", 2);
		return (NULL);
	}
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putstr_fd("Impossible d'ouvrire le fichier\n", 2);
		return (NULL);
	}
	i = 1;
	while (get_next_line(fd, &ptr->tmp) > 0)
	{
		if (!(ptr->map = malloc(sizeof(char *) * i)))
	}
	if (chech_line(ptr->map))
	return (ptr);
}
