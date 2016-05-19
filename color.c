/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 22:39:24 by rbohmert          #+#    #+#             */
/*   Updated: 2016/05/19 02:51:15 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_pas(t_point p1, t_point p2, t_algo *al)
{
	al->z = (double)p1.z;
	al->pas_z = (double)(p2.z - p1.z) / sqrt(((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y)));
}

int		concat(int r, int g, int b)
{
	int ret;

	ret = 0;
	g = g > 255 ? 255 : g;
	g = g < 0 ? 0 : g;
	r = r > 255 ? 255 : r;
	r = r < 0 ? 0 : r;
	b = b > 255 ? 255 : b;
	b = b < 0 ? 0 : b;
	ret = r << 24;
	ret = ret | g << 16;
	ret = ret | b << 8;
	return (ret);
}

int		find_color(int z, t_infos *i)
{
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 255;
	b = 0;
	if (z >= 0 && z < i->zmax / 2)
		r = (255 * z) / (i->zmax / 2);
	else if (z >= i->zmax / 2)
	{
		r = 255;
		g = 255 - ((255 * z) / i->zmax);
	}
	else if (z < 0 && z > i->zmin / 2)
		b = (255 * abs(z)) / (abs(i->zmin) / 2);
	else if (z <= i->zmin / 2)
	{
		g = 255 - ((255 * abs(z)) / abs(i->zmin));
		b = 255;
	}
	return(concat(r, g, b));
}
