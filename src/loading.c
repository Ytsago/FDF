/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:28:06 by secros            #+#    #+#             */
/*   Updated: 2025/02/27 15:55:05 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_pict	new_image(t_data *data, char *path)
{
	t_pict	img;

	img.img = mlx_xpm_file_to_image(data->mlx_info.mlx, path, \
	&img.size.x, &img.size.y);
	if (!img.img)
		write (2, "Failed to load asset\n", 21);
	else
		img.addr = mlx_get_data_addr(img.img, &img.bytes, \
		&img.l_len, &img.endian);
	return (img);
}

int	load_anim(t_data *data, t_pict *entity)
{
	int	i;

	i = 0;
	entity[IDLE] = new_image(data, I_PLAYER);
	entity[FORW] = new_image(data, F_PLAYER);
	entity[BACK] = new_image(data, B_PLAYER);
	while (i < BACK + 1)
		if (!entity[i++].img)
			return (1);
	return (0);
}

void	load_asset(t_data *data)
{
	t_sprite	as;
	int			error;

	as.wall = new_image(data, WALL);
	as.tile = new_image(data, TILE);
	as.obj = new_image(data, OBJ);
	as.c_ex = new_image(data, CEXIT);
	as.wall2 = new_image(data, WALL2);
	as.o_ex = new_image(data, OEXIT);
	as.end = new_image(data, END);
	data->sprite = as;
	error = load_anim(data, (t_pict *)&data->sprite.play);
	if (!as.c_ex.img || !as.obj.img || error || !as.o_ex.img
		|| !as.end.img || !as.tile.img || !as.wall.img || !as.wall2.img)
		clean_exit(data, 1);
}

void	resolution(t_data *data)
{
	if (data->engine.set == LOW)
	{
		data->mlx_info.w_size->x = 1080;
		data->mlx_info.w_size->y = 720;
	}
	if (data->engine.set == MEDIUM)
	{
		data->mlx_info.w_size->x = 1920;
		data->mlx_info.w_size->y = 1080;
	}
	if (data->engine.set == HIGH)
	{
		data->mlx_info.w_size->x = 2560;
		data->mlx_info.w_size->y = 1440;
	}
	if (data->engine.set == MAX)
	{
		data->mlx_info.w_size->x = 3840;
		data->mlx_info.w_size->y = 2160;
	}
}
