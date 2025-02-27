/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:20:49 by secros            #+#    #+#             */
/*   Updated: 2025/02/27 16:02:44 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	merge_image(t_pict screen, t_pict *img, t_data *data, int frame)
{
	int		i;
	int		j;
	char	*pixel;
	char	*color;

	(void) data;
	i = 0;
	color = 0;
	while (i < ASSET)
	{
		j = 0;
		while (j < ASSET)
		{
			pixel = &screen.addr[i * screen.l_len + j * screen.bytes / 8];
			color = get_color(img, i, j, frame);
			if (*(int *) color == -16777216)
				color = get_asset(data, (t_vect){j, i});
			*(unsigned int *) pixel = *(unsigned int *) color;
			j++;
		}
		i++;
	}
}

static void	draw_tiles(t_data *data, int x[2], int y[2], t_vect offset_pix)
{
	t_pict	*img;

	if (data->map[y[1]][x[1]] == '\n' || data->map[y[1]][x[1]] == '\0')
		return ;
	else if (data->map[y[1]][x[1]] == '2' || data->map[y[1]][x[1]] == '0')
		img = &data->sprite.tile;
	else if (data->map[y[1]][x[1]] == 'e' && data->engine.obj > 0)
		img = &data->sprite.c_ex;
	else if (data->map[y[1]][x[1]] == 'e' && data->engine.obj == 0)
		img = &data->sprite.o_ex;
	else if (data->map[y[1]][x[1]] == 'c')
		img = &data->sprite.obj;
	else if (data->map[y[1] + 1] && data->map[y[1] + 1][x[1]] == '1'
		&& data->map[y[1]][x[1]] == '1')
		img = &data->sprite.wall2;
	else if (data->map[y[1]][x[1]] == '1')
		img = &data->sprite.wall;
	else
		img = &data->sprite.tile;
	mlx_put_image_to_window(data->mlx_info.mlx, \
		data->mlx_info.win, img->img, x[0] * ASSET - offset_pix.x, y[0] * ASSET - offset_pix.y);
}

static void	draw_world(t_data *data, t_vect offset, t_vect offset_pix)
{
	int	y[2];
	int	x[2];

	y[0] = 0;
	y[1] = y[0] + offset.y;
	while (y[0] <= data->mlx_info.w_size->y / ASSET + 2 && data->map[y[1]])
	{
		x[0] = 0;
		x[1] = x[0] + offset.x;
		while (x[0] <= data->mlx_info.w_size->x + 1 \
		/ ASSET && data->map[y[1]][x[1]])
		{
			draw_tiles(data, x, y, offset_pix);
			x[1]++;
			x[0]++;
		}
		y[1]++;
		y[0]++;
	}
	
}

void	select_frame(t_data *data, t_pict *sprt)
{
	static int 	frame;
	static int	dir;

	frame = frame % 50;
	if (data->player.acc.x > 0)
	{
		if (dir != FORW)
			frame = 0;
		merge_image(data->engine.screen, &sprt[FORW], data, frame / FRAME_SPEED % 4);
		frame++;
		dir = FORW;
	}
	else if (data->player.acc.x < 0)
	{
		if (dir != BACK)
			frame = 0;
		merge_image(data->engine.screen, &sprt[BACK], data, frame / FRAME_SPEED % 4);
		frame++;
		dir = BACK;
	}
	else if (data->player.acc.x == 0)
	{
		if (dir != IDLE)
			frame = 0;
		merge_image(data->engine.screen, &sprt[IDLE], data, frame / FRAME_SPEED % 4);
		frame++;
		dir = IDLE;
	}
}
t_vect	compute_offset_x(t_data *data)
{
	t_vect	offset;

}
void	world_init(t_data *data)
{
	t_vect	offset;
	t_vect	offset_pix;

	offset.x = data->mlx_info.w_size->x / (2 * ASSET);
	offset.x = data->player.pos.x / ASSET - offset.x;
	offset_pix.x = data->player.pos.x % ASSET;
	if (data->player.pos.x / ASSET + (offset_pix.x > 0) + data->mlx_info.w_size->x / (2 * ASSET) > \
		(int) ft_strlen(data->map[0]) - 2 + (data->mlx_info.w_size->x % (2 * ASSET) == 0))
	{
		offset.x = ft_strlen(data->map[0]) - 2 + (data->mlx_info.w_size->x \
		% (2 * ASSET) == 0) - data->mlx_info.w_size->x / ASSET;
		offset_pix.x = 0;
	}
	if (((offset.x * ASSET - offset_pix.x) / ASSET) < 0)
	{
		offset.x = 0;
		offset_pix.x = 0;
	}
	offset_pix.y = data->player.pos.y % ASSET;
	offset.y = data->mlx_info.w_size->y / (2 * ASSET);
	offset.y = data->player.pos.y / ASSET - offset.y;
	if (data->player.pos.y / ASSET + (offset_pix.y > 0) + data->mlx_info.w_size->y / (2 * ASSET) > \
	(int) ft_tablen(data->map) - 1)
	{
		offset.y = ft_tablen(data->map) - 1 + (data->mlx_info.w_size->x \
		% (2 * ASSET) != 0) + (data->mlx_info.w_size->y % (2 * ASSET) == 112) \
		- data->mlx_info.w_size->y / ASSET;
		offset_pix.y = 0;
	}
	if (offset.y * ASSET + offset_pix.y < 0)
	{
		offset.y = 0;
		offset_pix.y = 0;
	}
	draw_world(data, offset, offset_pix);
	select_frame(data, data->sprite.play);
	mlx_put_image_to_window(data->mlx_info.mlx, data->mlx_info.win, data->engine.screen.img, data->player.pos.x - offset.x * ASSET - offset_pix.x ,data->player.pos.y - offset.y * ASSET - offset_pix.y);
}
