/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 19:00:46 by rbohmert          #+#    #+#             */
/*   Updated: 2016/02/24 08:44:16 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	calcul(t_point *p, t_infos *i)
{
	t_point pnew;

	pnew.x = i->xstart + ((sqrt(2) / 2) * ((p->x * i->zoom) - (p->y * i->zoom)));
	pnew.y = i->ystart - ((sqrt(2.0 / 3.0) * (p->z * i->zoom / i->prof)) - ((1 / sqrt(6)) * (i->zoom * (p->x + p->y))));
	return (pnew);
}

void	put_img(t_infos *i)
{
	i->img = mlx_new_image(i->mlx, WIDTH, HEIGTH);
	i->ptr_img = mlx_get_data_addr(i->img, &(i->bpp), &(i->img_line), &(i->endian));
	put_map(i);
	mlx_put_image_to_window(i->mlx, i->win,i->img, 0, 0);
	mlx_destroy_image(i->mlx, i->img);
}

void	put_map(t_infos *i)
{
	t_list *tmp;

	tmp = i->list;
	while (tmp->next)
	{
		if ((((t_point *)tmp->content)->nb  % i->line_size) != 0)
			put_line(calcul(tmp->content, i), calcul(tmp->next->content, i), i);
		if (!(((t_point *)tmp->content)->nb > (i->line_size * (i->nb_line - 1))))
			put_line(calcul(tmp->content, i), calcul(get_lst_nb(tmp, i), i), i);
		tmp = tmp->next;
	}
}

void	put_line(t_point p1, t_point p2, t_infos *i) 
{
	int dx = abs((p2.x - p1.x)), sx = p1.x<p2.x ? 1 : -1;
	int dy = abs((p2.y - p1.y)), sy = p1.y<p2.y ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;

	while (!(p1.x == p2.x && p1.y == p2.y)){
		put_pixel(p1.x, p1.y, 0xFFFFFF, i);
		e2 = err;
		if (e2 >-dx) { err -= dy; p1.x += sx; }
		if (e2 < dy) { err += dx; p1.y += sy; }
	}
}

void	put_pixel(int x, int y, int color, t_infos *i)
{
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGTH)
	{
		i->ptr_img[(i->img_line * y) + (4 * x) + 2] = 255;
		i->ptr_img[(i->img_line * y) + (4 * x) + 1] = 255;
		i->ptr_img[(i->img_line * y) + (4 * x)] = 255;
	}
}
