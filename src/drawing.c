/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:20:49 by secros            #+#    #+#             */
/*   Updated: 2025/02/23 18:45:24 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_cursor(t_pict *img, int x, int y)
{
	int		i;
	int		j;
	char	*pixel;

	i = 0;
	while (i < 30)
	{
		j = 0;
		while ((j < 2 * i && i <= 15) || (i > 15 && j < 60 - i * 2))
		{
			pixel = &img->addr[(y + i) * img->l_len + (x + j) * img->bytes / 8];
			*(unsigned int *) pixel = 0xFF0000;
			j++;
		}
		i++;
	}
}

void	erease_cursor(t_pict *img, int x, int y)
{
	int		i;
	int		j;
	char	*pixel;

	i = 0;
	while (i < 30)
	{
		j = 0;
		while ((j < 2 * i && i <= 15) || (i > 15 && j < 60 - i * 2))
		{
			pixel = &img->addr[(y + i) * img->l_len + (x + j) * img->bytes / 8];
			*(unsigned int *) pixel = 0x432a73;
			j++;
		}
		i++;
	}
}

char	*get_color(t_pict img, int i, int j)
{
	return (&img.addr[i * img.l_len + j * img.bytes / 8]);
}

void	merge_image(t_pict screen, t_pict test, t_vect pos)
{
	int		i;
	int		j;
	char	*pixel;
	char	*color;

	(void) test;
	i = 0 + pos.y;
	color = 0;
	while (i < 64)
	{
		j = 0 + pos.y;
		while (j < 64)
		{
			pixel = &screen.addr[i * screen.l_len + j * screen.bytes / 8];
			color = get_color(test, i , j);
			if (*(int *) color != -16777216)
				*(unsigned int *) pixel = *(unsigned int *) color;
			j++;
		}
		i++;
	}
}

static void	draw_tiles(t_data *data, size_t x[2], size_t y[2])
{
	t_pict	*img;

	if (data->map[y[1]][x[1]] == '\n' || data->map[y[1]][x[1]] == '\0')
		return ;
	if (data->map[y[1]][x[1]] == 'p')
		img = &data->sprite.play;
	if (data->map[y[1]][x[1]] == '1')
		img = &data->sprite.wall;
	if (data->map[y[1]][x[1]] == '2' || data->map[y[1]][x[1]] == '0')
		img = &data->sprite.tile;
	if (data->map[y[1]][x[1]] == 'e' && data->engine.obj > 0)
		img = &data->sprite.c_ex;
	if (data->map[y[1]][x[1]] == 'e' && data->engine.obj == 0)
		img = &data->sprite.o_ex;
	if (data->map[y[1]][x[1]] == 'c')
		img = &data->sprite.obj;
	if (data->map[y[1] + 1] && data->map[y[1] + 1][x[1]] == '1'
		&& data->map[y[1]][x[1]] == '1')
		img = &data->sprite.wall2;
	mlx_put_image_to_window(data->mlx_info.mlx, \
		data->mlx_info.win, img->img, x[0] * 64, y[0] * 64);
}

static void	draw_world(t_data *data, size_t i, size_t j)
{
	size_t			y[2];
	size_t			x[2];

	y[0] = 0;
	y[1] = y[0] + j;
	while (y[0] <= data->mlx_info.w_size[1] / 64 && data->map[y[1]])
	{
		x[0] = 0;
		x[1] = x[0] + i;
		while (x[0] <= data->mlx_info.w_size[0] + 1 \
		/ 64 && data->map[y[1]][x[1]])
		{
			draw_tiles(data, x, y);
			x[1]++;
			x[0]++;
		}
		y[1]++;
		y[0]++;
	}
}

void	world_init(t_data *data)
{
	int	i;
	int	j;

	i = data->mlx_info.w_size[0] / 128;
	j = data->mlx_info.w_size[1] / 128;
	i = data->player.pos.x / 64 - i;
	if (data->player.pos.x / 64 + data->mlx_info.w_size[0] / 128 > \
		ft_strlen(data->map[0]) - 2 + (data->mlx_info.w_size[0] % 128 == 0))
		i = ft_strlen(data->map[0]) - 2 + (data->mlx_info.w_size[0] % 128 == 0) \
			- data->mlx_info.w_size[0] / 64;
	if (i < 0)
		i = 0;
	j = data->player.pos.y / 64 - j;
	if (data->player.pos.y / 64 + data->mlx_info.w_size[1] / 128 > \
	ft_tablen(data->map) - 1)
		j = ft_tablen(data->map) - 1 + (data->mlx_info.w_size[0] % 128 != 0) + \
		(data->mlx_info.w_size[1] % 128 == 112) - data->mlx_info.w_size[1] / 64;
	if (j < 0)
		j = 0;
	draw_world(data, i, j);
}
