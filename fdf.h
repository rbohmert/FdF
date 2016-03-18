/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 19:04:50 by rbohmert          #+#    #+#             */
/*   Updated: 2016/02/24 07:55:49 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# define HEIGTH 2000
# define WIDTH 1800

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			nb;
}				t_point;

typedef struct	s_infos
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*ptr_img;
	t_list		*list;
	int			nb_line;
	int			line_size;
	int			bpp;
	int			img_line;
	int			endian;
	int			xstart;
	int			ystart;
	int			zoom;
	int			prof;
}				t_infos;

void	init_info(t_infos *i);
t_point *get_lst_nb(t_list *list, t_infos *info);
void	add_pixel(int x, int y, int z, t_infos *i);
void	get_coord(char *filename, t_infos *i);
void	put_img(t_infos *i);
void	put_map(t_infos *i);
void	put_line(t_point p1, t_point p2, t_infos *i);
void	put_pixel(int x, int y, int color, t_infos *i);
t_point	calcul(t_point *p, t_infos *i);

#endif
