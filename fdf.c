/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 16:32:47 by rbohmert          #+#    #+#             */
/*   Updated: 2016/02/24 08:31:00 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_hook(int key, t_infos *i)
{
	printf("key : %d\n", key);
	(key == 53) ? exit(2) : 0;
	i->zoom += (key == 69) ? 1 : 0;
	i->zoom -= (key == 78 && i->zoom > 1) ? 1 : 0;
	i->xstart += (key == 124) ? i->zoom * 10 : 0;
	i->xstart -= (key == 123) ? i->zoom * 10 : 0;
	i->ystart += (key == 125) ? i->zoom * 10 : 0;
	i->ystart -= (key == 126) ? i->zoom * 10 : 0;
	i->prof -= (key == 116 && i->prof > 1) ? 1 : 0;
	i->prof += (key == 121) ? 1 : 0;
	put_img(i);
	return (1);
}

void init_info(t_infos *i)
{
	i->list = NULL;
	i->xstart = 400;
	i->ystart = 150;
	i->zoom = 10;
	i->prof = 5;
}

t_point *get_lst_nb(t_list *list, t_infos *info)
{
	int 	i;
	t_list	*tmp;

	tmp = list;
	i = -1;
	while (++i < info->line_size)
		tmp = tmp->next;
	return((t_point *)tmp->content);
}

int main (int ac, char **av)
{
	t_infos	i;

	(ac == 1) ? printf("no arg") : 0;
	i.mlx = mlx_init();
	i.win = mlx_new_window(i.mlx, WIDTH, HEIGTH, "mlx 42");
	init_info(&i);
	get_coord(av[1], &i);
	put_img(&i);
	mlx_key_hook(i.win, key_hook, &i); 
	mlx_loop(i.mlx);
}
