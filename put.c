/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 19:00:46 by rbohmert          #+#    #+#             */
/*   Updated: 2016/05/19 02:45:53 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	calcul(t_point *p, t_infos *i, int mode)
{
	t_point pnew;

	if (mode)
	{
		pnew.x = i->xstart + ((p->x * i->zoom) + 0.35 * (p->y * i->zoom));
		pnew.y = i->ystart - ((p->z * i->zoom / i->prof) - 0.35 * (p->y * i->zoom));
	}
	else
	{
		pnew.x = i->xstart + ((sqrt(2) / 2) * ((p->x * i->zoom) - (p->y * i->zoom)));
		pnew.y = (i->ystart - 50) - ((sqrt(2.0 / 3.0) * (p->z * i->zoom / i->prof)) - ((1 / sqrt(6)) * (i->zoom * (p->x + p->y))));
	}
	pnew.z = p->z;
	return (pnew);
}

void	put_img(t_infos *i, int mode)
{
	i->img = mlx_new_image(i->mlx, WIDTH, HEIGTH);
	i->ptr_img = mlx_get_data_addr(i->img, &(i->bpp), &(i->img_line), &(i->endian));
	put_map(i, mode);
	if (!mode)
		mlx_put_image_to_window(i->mlx, i->win,i->img, 0, 0);
	else
		mlx_put_image_to_window(i->mlx, i->win2,i->img, 0, 0);
	if (i->show)
		put_indic(i, mode);
	mlx_destroy_image(i->mlx, i->img);
}

void	put_map(t_infos *i, int mode)
{
	t_list *tmp;

	tmp = i->list;
	while (tmp->next)
	{
		if ((((t_point *)tmp->content)->nb  % i->line_size) != 0)
			put_line(calcul(tmp->content, i, mode), calcul(tmp->next->content, i, mode), i);
		if (!(((t_point *)tmp->content)->nb > (i->line_size * (i->nb_line - 1))))
			put_line(calcul(tmp->content, i, mode), calcul(get_lst_nb(tmp, i), i, mode), i);
		tmp = tmp->next;
	}
}

void put_line(t_point p1, t_point p2, t_infos *i)
{
	t_algo		algo;

	algo.dx = abs((p2.x - p1.x));
	algo.sx = p1.x < p2.x ? 1 : -1;
	algo.dy = abs((p2.y - p1.y));
	algo.sy = p1.y < p2.y ? 1 : -1;
	algo.err = (algo.dx > algo.dy ? algo.dx : -algo.dy) / 2;
	get_pas(p1, p2, &algo);
	while (!(p1.x == p2.x && p1.y == p2.y))
	{
		put_pixel(p1.x, p1.y, find_color(algo.z, i), i);
		algo.z += algo.pas_z;
		algo.e2 = algo.err;
		if (algo.e2 > -algo.dx)
		{
			algo.err -= algo.dy;
			p1.x += algo.sx;
		}
		if (algo.e2 < algo.dy)
		{
			algo.err += algo.dx;
			p1.y += algo.sy;
		}
	}
}

void	put_pixel(int x, int y, int color, t_infos *i)
{
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGTH)
	{
		i->ptr_img[(i->img_line * y) + (i->bpp / 8 * x) + 2] = (color & 0xFF000000) >> 24;
		i->ptr_img[(i->img_line * y) + (i->bpp / 8 * x) + 1] = (color & 0x00FF0000) >> 16;
		i->ptr_img[(i->img_line * y) + (i->bpp / 8 * x)] = (color & 0x0000FF00) >> 8;
	}
}
