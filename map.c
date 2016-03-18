/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 19:43:56 by rbohmert          #+#    #+#             */
/*   Updated: 2016/02/24 08:28:17 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_pixel(int x, int y, int z, t_infos *i)
{
	t_point	*p;
	static int nb = 1;
	if (!(p = (t_point *)malloc(sizeof(t_point))))
		exit(2);
	p->x = x;
	p->y = y;
	p->z =  z;
	p->nb = nb;
	nb++;
	ft_push_back(&(i->list), p, 0);
}

void	get_coord(char *filename, t_infos *i)
{
	int fd;
	int y;
	int x;
	char *line;
	char **tmp;

	y = 0;
	fd = open(filename, O_RDWR);
	while (get_next_line(fd, &line) > 0)
	{
		x = 0;
		tmp = ft_strsplit(line, ' ');
		while (tmp[x])
		{
			add_pixel(x, y, ft_atoi(tmp[x]), i);
			x++;
		}
		free(tmp);
		free(line);
		i->line_size = x;
		y++;
	}
	i->nb_line = y;
	close(fd);
}
