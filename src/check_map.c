/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:07:57 by secros            #+#    #+#             */
/*   Updated: 2024/12/20 13:24:37 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static size_t	check_ex_row(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	return (i);
}

static size_t	check_line(char *str)
{
	size_t	i;

	i = 0;
	if (str[i++] != '1')
		return (0);
	while (str[i] != '\n')
	{
		if (str[i] == '1' || str[i] == 'P' || str[i] == 'C'
			|| str[i] == 'E' || str[i] == '0')
			i++;
		else
			return (0);
	}
	if (str[i - 1] != '1')
		return (0);
	return (i);
}

int	check_map(char **map)
{
	size_t	len;
	size_t	i;

	i = 1;
	len = check_ex_row(map[0]);
	if (len < 4)
		return (1);
	while (map[i] && map[i + 1])
		if (len != check_line(map[i++]))
			return (1);
	if (len != check_ex_row(map[i]))
		return (1);
	return (0);
}

static int	set_player(t_data *data, size_t x, size_t y)
{
	if (data->player.pos_x == 0 && data->player.pos_y == 0)
	{
		data->player.pos_x = x;
		data->player.pos_y = y;
		return (0);
	}
	return (1);
}

int	check_data(t_data *data, char **map)
{
	size_t	i;
	size_t	j;
	int		count[2];

	j = 0;
	count[0] = 0;
	count[1] = 0;
	while (map[++j])
	{
		i = 0;
		while (map[j][++i])
		{
			if (map[j][i] == 'P')
				if (set_player(data, i, j))
					return (1);
			if (map[j][i] == 'C')
				count[0]++;
			if (map[j][i] == 'E')
				count[1]++;
		}
	}
	if (count[0] > 0 && count[1] == 1)
		return (0);
	return (1);
}
