/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 19:43:56 by rbohmert          #+#    #+#             */
/*   Updated: 2016/05/27 02:22:46 by rbohmert         ###   ########.fr       */
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

void	check_length(int x, int y, t_infos *i)
{
	if (y == 0)
		i->line_size = x;
	else if (y != 0 && x != i->line_size)
		error("Bad file.");
}

void	check(char *filename)
{
	char	str[2];
	int		fd;

	if ((fd = open(filename, O_RDWR)) < 0)
		error("Unable to open file.");
	if (!(read(fd, str, 1)))
		error("No data found.");
	if (!ft_isdigit(str[0]) && str[0] != ' ' && str[0] != '-')
		error("Bad data.");
	close(fd);
}

void	get_coord(char *filename, t_infos *i)
{
	int		fd;
	int		y;
	int		x;
	char	*line;
	char	**tmp;

	y = 0;
	check(filename);
	fd = open(filename, O_RDWR);
	tmp = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		x = -1;
		tmp = ft_strsplit(line, ' ');
		while (tmp[++x])
			add_pixel(x, y, ft_atoi(check_str(tmp[x])), i);
		free(tmp);
		free(line);
		check_length(x, y, i);
		y++;
	}
	i->nb_line = y;
	close(fd);
}
