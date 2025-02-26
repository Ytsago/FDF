/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:22:00 by secros            #+#    #+#             */
/*   Updated: 2025/02/26 04:08:17 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "ft_printf.h"

/* static void	check_pos(t_data *data)
{
	int	x;
	int	y;
	int	count;

	x = data->player.pos.x / 64;
	y = data->player.pos.y / 64;
	count = 0;
	if (data->map[y][x] == 'c')
	{
		data->map[y][x] = 'C';
		data->engine.obj--;
	}
	else if (data->map[y][x] == 'e' && data->engine.obj == 0)
		end_game(data);
}

static void	moving(t_data *data, int dir)
{
	data->engine.move++;
	// data->map[*y / 64][*x / 64] = '2';
	if (ft_printf("move :%d\n", data->engine.move) == -1)
		return ((void) clean_exit(data, 1));
	if (dir == 1)
		data->player.acc.y = -1;
	else if (dir == 2)
		data->player.acc.x = 1;
	else if (dir == 3)
		data->player.pos.x -= 1;
	else if (dir == 4)
		data->player.pos.y += 1;
	check_pos(data);
	// data->map[*y / 64][*x / 64] = 'p';
}
 */
int	input(int key, void *param)
{
	t_data *data;

	data = param;
	if (key == SPACE)
		data->player.acc.y = -5;
	if (key == D_KEY)
		data->player.acc.x = +1;
	if (key == S_KEY)
		data->player.acc.y = +1;
	if (key == A_KEY)
		data->player.acc.x = -1;
	if (key == ESCAPE)
		clean_exit(data, 0);
	return (1);
}

int	key_release(int key, t_data *data)
{
	if (key == SPACE)
		data->player.acc.y = 0;
	if (key == D_KEY)
		data->player.acc.x = 0;
	if (key == S_KEY)
		data->player.acc.y = 0;
	if (key == A_KEY)
		data->player.acc.x = 0;
	return (1);
}