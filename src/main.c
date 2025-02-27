/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:16:20 by secros            #+#    #+#             */
/*   Updated: 2025/02/27 11:07:38 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static void	data_init(t_data *data)
{
	data->mlx_info.mlx = mlx_init();
	if (!data->mlx_info.mlx)
	{
		write (2, "Error\nSomething went wrong", 26);
		free_the_mallocs(data->map);
		exit(1);
	}
	data->engine.move = 0;
	data->engine.end = 0;
	resolution(data);
	data->mlx_info.win = mlx_new_window(data->mlx_info.mlx, \
	data->mlx_info.w_size->x, data->mlx_info.w_size->y, TITLE);
	if (!data->mlx_info.win)
		clean_exit(data, 1);
	data->engine.screen.img =mlx_new_image(data->mlx_info.mlx, ASSET, ASSET);
	if (!data->engine.screen.img)
		return ((void) clean_exit(data, 1));
	data->engine.screen.addr = mlx_get_data_addr(data->engine.screen.img, \
	&data->engine.screen.bytes, \
	&data->engine.screen.l_len, &data->engine.screen.endian);
	load_asset(data);
}

void	end_game(t_data *data)
{
	size_t		x;
	size_t		y;
	void		*pt[3];

	x = data->mlx_info.w_size->x / 2 - 450;
	y = data->mlx_info.w_size->y / 2 - 350;
	pt[0] = data->mlx_info.mlx;
	pt[1] = data->mlx_info.win;
	pt[2] = data->sprite.end.img;
	data->engine.end = 1;
	mlx_clear_window(data->mlx_info.mlx, data->mlx_info.win);
	mlx_put_image_to_window(pt[0], pt[1], pt[2], x, y);
}

void	asset_init(t_sprite *sprt)
{
	sprt->c_ex.img = NULL;
	sprt->o_ex.img = NULL;
	sprt->obj.img = NULL;
	ft_bzero(&sprt->play, sizeof(t_pict) * 5);
	sprt->tile.img = NULL;
	sprt->wall.img = NULL;
	sprt->wall2.img = NULL;
	sprt->end.img = NULL;
}

int	launch(t_data *data)
{
	asset_init(&data->sprite);
	data_init(data);
	world_init(data);
	if (gettimeofday(&data->engine.time, NULL) == -1)
		clean_exit(data, 1);
	mlx_loop_hook(data->mlx_info.mlx, game_loop, data);
	mlx_hook(data->mlx_info.win, KeyPress, KeyPressMask, input, data);
	mlx_hook(data->mlx_info.win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->mlx_info.win, DestroyNotify, 0, close_button, data);
	mlx_loop(data->mlx_info.mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_pict	load;

	ft_bzero(&data, sizeof(t_data));
	if (ac != 2 || map_parsing(&data, av[1]))
	{
		if (ac != 2)
			write (2, "Error\nNot the right number of arguments", 40);
		return (1);
	}
	load.img = NULL;
	data.mlx_info.mlx = mlx_init();
	if (!data.mlx_info.mlx)
	{
		write (2, "Error\n failed to create mlx_ptr", 31);
		return (1);
	}
	data.mlx_info.win = mlx_new_window(data.mlx_info.mlx, 400, 500, TITLE);
	if (!data.mlx_info.win)
	{
		mlx_destroy_display(data.mlx_info.mlx);
		free (data.mlx_info.mlx);
		return ((void) write (2, "Error\nCan't create window", 25), 1);
	}
	loading_screen(&data, &load);
}
