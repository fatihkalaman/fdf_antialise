/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkalaman <student.42kocaeli.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:05:37 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/24 18:56:31 by fkalaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_set_r_map(t_vars *vars)
{
	int		x;
	int		y;

	x = 0;
	while (x < vars->map.axis)
	{
		y = 0;
		while (y < vars->map.ordinate)
		{
			vars->r_map[x][y].x = (x * vars->offset) + vars->origin.x;
			vars->r_map[x][y].y = (y * vars->offset) + vars->origin.y;
			vars->r_map[x][y].z = (vars->map.points[x][y].z * vars->offset);
			y++;
		}
		x++;
	}
}

static void	ft_draw_ordinate(t_vars *vars)
{
	int		x;
	int		y;

	y = 1;
	while (y <= vars->map.ordinate)
	{
		x = 1;
		while (x < vars->map.axis)
		{
			vars->p1.x = vars->r_map[x - 1][y - 1].x;
			vars->p1.y = vars->r_map[x - 1][y - 1].y;
			vars->p1.color = vars->map.points[x - 1][y - 1].color;
			vars->p2.x = vars->r_map[x][y - 1].x;
			vars->p2.y = vars->r_map[x][y - 1].y;
			vars->p2.color = vars->map.points[x][y - 1].color;
			ft_draw_line(vars);
			x++;
		}
		y++;
	}
}

static void	ft_draw_axis(t_vars *vars)
{
	int		x;
	int		y;

	x = 1;
	while (x <= vars->map.axis)
	{
		y = 1;
		while (y < vars->map.ordinate)
		{
			vars->p1.x = vars->r_map[x - 1][y - 1].x;
			vars->p1.y = vars->r_map[x - 1][y - 1].y;
			vars->p1.color = vars->map.points[x - 1][y - 1].color;
			vars->p2.x = vars->r_map[x - 1][y].x;
			vars->p2.y = vars->r_map[x - 1][y].y;
			vars->p2.color = vars->map.points[x - 1][y].color;
			ft_draw_line(vars);
			y++;
		}
		x++;
	}
}

void	ft_draw(t_vars *vars)
{
	if (vars->projection == 0)
	{
		vars->origin.x = ((WIDTH - ((vars->map.axis + vars->map.ordinate)
						* vars->x_offset)) / 2)
			+ (vars->x_offset * vars->map.ordinate);
		vars->origin.y = ((HEIGHT - ((vars->map.axis + vars->map.ordinate)
						* vars->y_offset)) / 2) + (vars->y_offset);
	}
	else
	{
		vars->origin.x = ((WIDTH - (vars->offset
						* (vars->map.axis))) + vars->offset) / 2;
		vars->origin.y = HEIGHT / 2;
	}
	vars->origin.x += vars->i;
	vars->origin.y += vars->j;
	ft_set_r_map(vars);
	if (vars->projection == 0)
		ft_projection_iso(vars);
	else
		ft_projection_parallel(vars);
	ft_draw_axis(vars);
	ft_draw_ordinate(vars);
}
