/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 16:32:47 by rbohmert          #+#    #+#             */
/*   Updated: 2016/05/19 03:29:56 by ppomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_hook(int key, t_infos *i)
{
	printf("key : %d\n", key);
	(key == 53) ? exit(2) : 0;
	i->zoom += (key == 69) ? 1 : 0;
	i->zoom -= (key == 78 && i->zoom > 1) ? 1 : 0;
	i->xstart += (key == 124) ? HEIGTH / 10 : 0;
	i->xstart -= (key == 123) ? HEIGTH / 10 : 0;
	i->ystart += (key == 125) ? WIDTH / 10 : 0;
	i->ystart -= (key == 126) ? WIDTH / 10 : 0;
	i->prof -= (key == 116 && i->prof > 1) ? 1 : 0;
	i->prof += (key == 121) ? 1 : 0;
	if (key == 44 && i->show)
		i->show = 0;
	else if (key == 44 && !i->show)
		i->show = 1;
	key == 49 ? init_info(i, i->path) : 0;
	put_img(i, 0);
	put_img(i, 1);
	return (1);
}

void	init_info(t_infos *i, char *path)
{
	i->show = 1;
	i->path = path;
	i->xstart = WIDTH / 2;
	i->ystart = HEIGTH / 2;
	i->zoom = 10;
	i->prof = 5;
}

t_point	*get_lst_nb(t_list *list, t_infos *info)
{
	int		i;
	t_list	*tmp;

	tmp = list;
	i = -1;
	while (++i < info->line_size)
		tmp = tmp->next;
	return ((t_point *)tmp->content);
}

int		main(int ac, char **av)
{
	t_infos	i;

	(ac == 1) ? printf("no arg") : 0;
	i.mlx = mlx_init();
	i.list = NULL;
	init_info(&i, av[1]);
	get_coord(av[1], &i);
	i.win = mlx_new_window(i.mlx, WIDTH, HEIGTH, "Perspective Isometrique");
	i.win2 = mlx_new_window(i.mlx, WIDTH, HEIGTH, "Perspective Cavaliere");
	put_img(&i, 0);
	put_img(&i, 1);
	mlx_hook(i.win, 2, 3, key_hook, &i);
	mlx_hook(i.win2, 2, 3, key_hook, &i);
	mlx_loop(i.mlx);
}
