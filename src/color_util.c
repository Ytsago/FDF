/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:56:54 by secros            #+#    #+#             */
/*   Updated: 2025/02/27 15:57:19 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*get_color(t_pict *img, int i, int j, int frame)
{
	(void) frame;
	return (&img->addr[i * img->l_len + (j + ((frame * ASSET) + 1)) * img->bytes / 8]);
}

char	*get_asset(t_data *data, t_vect pos_img)
{
	t_vect	pos;
	t_pict	*img;

	img = &data->sprite.tile;
	pos.x = (data->player.pos.x + pos_img.x);
	pos.y = (data->player.pos.y + pos_img.y);

	if (data->map[pos.y / ASSET][pos.x / ASSET] == '1' && data->map[pos.y / ASSET + 1] && data->map[pos.y / ASSET + 1][pos.x / ASSET] == '1')
		return (get_color(&data->sprite.wall2, pos.y % ASSET, pos.x % ASSET, 0));
	if (data->map[pos.y / ASSET][pos.x / ASSET] == '1')
		return (get_color(&data->sprite.wall, pos.y % ASSET, pos.x % ASSET, 0));
	if (data->map[pos.y / ASSET][pos.x / ASSET] == 'e' && data->engine.obj > 0)
		return (get_color(&data->sprite.c_ex, pos.y % ASSET, pos.x % ASSET, 0));
	if (data->map[pos.y / ASSET][pos.x / ASSET] == 'e' && data->engine.obj == 0)
		return (get_color(&data->sprite.o_ex, pos.y % ASSET, pos.x % ASSET, 0));
	if (data->map[pos.y / ASSET][pos.x / ASSET] == 'c')
		return (get_color(&data->sprite.obj, pos.y % ASSET, pos.x % ASSET, 0));
	if (data->map[pos.y / ASSET][pos.x / ASSET] == '2')
		return (get_color(&data->sprite.tile, pos.y % ASSET, pos.x % ASSET, 0));
	return (get_color(img, pos.y % ASSET, pos.x % ASSET, 0));
}
