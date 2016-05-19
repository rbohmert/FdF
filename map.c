/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 19:43:56 by rbohmert          #+#    #+#             */
/*   Updated: 2016/05/19 04:08:00 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_indic(t_infos *i, int mode)
{
	mlx_string_put(i->mlx, mode ? i->win2 : i->win,\
					5, 5, 0xFFFFFF, i->path);
	mlx_string_put(i->mlx, mode ? i->win2 : i->win,\
					300, 25, 0xFFFFFF, "CONTROLS:");
	mlx_string_put(i->mlx, mode ? i->win2 : i->win,\
					420, 25, 0xFFFFFF, "arrows = move;");
	mlx_string_put(i->mlx, mode ? i->win2 : i->win,\
					420, 45, 0xFFFFFF, "+ / - = zoom +/-;");
	mlx_string_put(i->mlx, mode ? i->win2 : i->win,\
					420, 65, 0xFFFFFF, "Pg up/down = depth +/-;");
	mlx_string_put(i->mlx, mode ? i->win2 : i->win,\
					800, 25, 0xFFFFFF, "? = hide/show instructions;");
	mlx_string_put(i->mlx, mode ? i->win2 : i->win,\
					800, 45, 0xFFFFFF, "space = reset params;");
	mlx_string_put(i->mlx, mode ? i->win2 : i->win,\
					800, 65, 0xFFFFFF, "ESC = quit;");
}

void	add_pixel(int x, int y, int z, t_infos *i)
{
	t_point		*p;
	static int	nb = 1;

	if (!(p = (t_point *)malloc(sizeof(t_point))))
		exit(2);
	p->x = x;
	p->y = y;
	p->z = z;
	p->nb = nb;
	if (z > i->zmax)
		i->zmax = z;
	if (z < i->zmin)
		i->zmin = z;
	nb++;
	ft_push_back(&(i->list), p, 0);
}

void	get_coord(char *filename, t_infos *i)
{
	int		fd;
	int		y;
	int		x;
	char	*line;
	char	**tmp;

	y = 0;
	if ((fd = open(filename, O_RDWR)) < 0)
		error("unable to open file");
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
