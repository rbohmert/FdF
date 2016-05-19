/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 19:04:50 by rbohmert          #+#    #+#             */
/*   Updated: 2016/05/19 03:47:13 by ppomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# define L(a) ((t_point *)(a->content))
# define HEIGTH 1250
# define WIDTH 1275

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	int					nb;
}						t_point;

typedef struct			s_infos
{
	void				*mlx;
	void				*win;
	void				*win2;
	void				*img;
	char				*ptr_img;
	char				*path;
	t_list				*list;
	int					show;
	int					nb_line;
	int					line_size;
	int					bpp;
	int					img_line;
	int					endian;
	int					xstart;
	int					ystart;
	int					zoom;
	int					prof;
	int					zmax;
	int					zmin;
}						t_infos;

typedef struct			s_algo
{
	int					dx;
	int					sx;
	int					dy;
	int					sy;
	int					err;
	int					e2;
	double				pas_z;
	double				z;
}						t_algo;

int						key_hook(int key, t_infos *i);
void					init_info(t_infos *i, char *path);
t_point					*get_lst_nb(t_list *list, t_infos *info);

void					put_indic(t_infos *i, int mode);
void					add_pixel(int x, int y, int z, t_infos *i);
void					get_coord(char *filename, t_infos *i);

t_point					calcul(t_point *p, t_infos *i, int mode);
void					put_img(t_infos *i, int mode);
void					put_map(t_infos *i, int mode);
void					put_line(t_point p1, t_point p2, t_infos *i);
void					put_pixel(int x, int y, int color, t_infos *i);

void					get_pas(t_point p1, t_point p2, t_algo *al);
void					put_indic(t_infos *i, int mode);
int						find_color(int z, t_infos *i);

#endif
