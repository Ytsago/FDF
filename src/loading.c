/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:28:06 by secros            #+#    #+#             */
/*   Updated: 2025/02/23 10:12:54 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_pict	new_image(t_data *data, char *path)
{
	t_pict	img;
	int		x;
	int		y;

	img.img = mlx_xpm_file_to_image(data->mlx_info.mlx, path, &x, &y);
	if (!img.img)
		write (2, "Failed to load asset\n", 21);
	else
		img.addr = mlx_get_data_addr(img.img, &img.bytes, \
		&img.l_len, &img.endian);
	return (img);
}

void	load_asset(t_data *data)
{
	t_sprite	as;

	as.wall = new_image(data, WALL);
	as.play = new_image(data, PLAYER);
	as.tile = new_image(data, TILE);
	as.obj = new_image(data, OBJ);
	as.c_ex = new_image(data, CEXIT);
	as.wall2 = new_image(data, WALL2);
	as.o_ex = new_image(data, OEXIT);
	as.end = new_image(data, END);
	data->sprite = as;
	if (!as.c_ex.img || !as.obj.img || !as.play.img || !as.o_ex.img
		|| !as.end.img || !as.tile.img || !as.wall.img || !as.wall2.img)
		clean_exit(data, 1);
}

void	resolution(t_data *data)
{
	if (data->engine.set == LOW)
	{
		data->mlx_info.w_size[0] = 1080;
		data->mlx_info.w_size[1] = 720;
	}
	if (data->engine.set == MEDIUM)
	{
		data->mlx_info.w_size[0] = 1920;
		data->mlx_info.w_size[1] = 1080;
	}
	if (data->engine.set == HIGH)
	{
		data->mlx_info.w_size[0] = 2560;
		data->mlx_info.w_size[1] = 1440;
	}
	if (data->engine.set == MAX)
	{
		data->mlx_info.w_size[0] = 3840;
		data->mlx_info.w_size[1] = 2160;
	}
}
