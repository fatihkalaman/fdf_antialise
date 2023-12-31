/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkalaman <student.42kocaeli.com.tr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/24 18:56:11 by fkalaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <math.h>

static void	ft_clear_win(t_vars *vars)
{
	int	j;

	j = WIDTH * HEIGHT * 4;
	ft_bzero(vars->data_addr, j);
}

static void	ft_calculate_offset(t_vars	*vars)
{
	float	x_offset;
	float	y_offset;

	x_offset = WIDTH * 0.8;
	x_offset = x_offset / (vars->map.axis + vars->map.ordinate);
	y_offset = HEIGHT * 0.8;
	y_offset = y_offset / (vars->map.axis + vars->map.ordinate);
	if (HEIGHT / y_offset > WIDTH / x_offset)
	{
		vars->x_offset = x_offset;
		vars->y_offset = x_offset * tan(vars->angle * M_PI / 180);
		vars->offset = y_offset / sin(vars->angle * M_PI / 180);
	}
	else
	{
		vars->x_offset = y_offset / tan(vars->angle * M_PI / 180);
		vars->y_offset = y_offset;
		vars->offset = y_offset / sin(vars->angle * M_PI / 180);
	}
}

static int	ft_loop_mlx(t_vars *vars)
{
	ft_clear_win(vars);
	ft_draw(vars);
	mlx_put_image_to_window(vars->m.mlx, vars->m.win, vars->img_ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	if (argc == 2)
	{
		vars = &(t_vars){0};
		vars->angle = 30;
		ft_check_map(argv[1], vars);
		ft_vars_init(vars);
		ft_calculate_offset(vars);
		mlx_loop_hook(vars->m.mlx, ft_loop_mlx, vars);
		ft_hooks(vars);
		mlx_loop(vars->m.mlx);
	}
	else
		write(2, "Usage: ./fdf <filename>\n", 24);
	return (0);
}
