/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:06:09 by secros            #+#    #+#             */
/*   Updated: 2024/12/20 11:38:00 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_wall(size_t x, size_t y, char **map)
{
	if (map[y][x] >= 'A' && map[y][x] <= 'Z')
	{
		map[y][x] = ft_tolower(map[y][x]);
		return (1);
	}
	if (map[y][x] == '0')
	{
		map[y][x] = '2';
		return (1);
	}
	return (0);
}

static void	pathing(size_t x, size_t y, char **map)
{
	if (is_wall(x + 1, y, map))
		pathing(x + 1, y, map);
	if (is_wall(x - 1, y, map))
		pathing(x - 1, y, map);
	if (is_wall(x, y + 1, map))
		pathing(x, y + 1, map);
	if (is_wall(x, y - 1, map))
		pathing(x, y - 1, map);
}

int	all_access(t_data *data, char **map)
{
	size_t	i;
	size_t	j;

	j = 0;
	pathing(data->player.pos_x, data->player.pos_y, map);
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'E' || map[j][i] == 'C')
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}
