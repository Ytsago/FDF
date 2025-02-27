/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_change.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:43:52 by secros            #+#    #+#             */
/*   Updated: 2025/02/27 15:56:30 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	change_resolution(t_data *data)
{
	if (data->engine.set == LOW)
		data->mlx_info.w_size->y = 66;
	else if (data->engine.set == MEDIUM)
		data->mlx_info.w_size->y = 166;
	else if (data->engine.set == HIGH)
		data->mlx_info.w_size->y = 266;
	else if (data->engine.set == MAX)
		data->mlx_info.w_size->y = 366;
	else
		data->mlx_info.w_size->y = 66;
}

void	change_selection(t_data *data)
{
	draw_cursor(data->load, data->mlx_info.w_size->x, \
	data->mlx_info.w_size->y);
	mlx_put_image_to_window(data->mlx_info.mlx, \
	data->mlx_info.win, data->load->img, 0, 0);
}
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
