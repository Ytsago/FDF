/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:53:36 by secros            #+#    #+#             */
/*   Updated: 2025/02/26 14:20:42 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	step_count(t_data *data)
{
	char	*str;
	char	*step;

		step = ft_itoa(data->engine.move);
		if (!step)
			clean_exit(data, 1);
		str = ft_strjoin("Step :", step);
		free (step);
		if (!str)
			clean_exit(data, 1);
		mlx_string_put(data->mlx_info.mlx, data->mlx_info.win, 15, 15, 0, str);
		free (str);
}

int check_collision(t_data *data, t_hitbox hitbox, t_vect velo, char c)
{
	if (data->map[(data->player.pos.y + hitbox.top.y + velo.y) / ASSET][(data->player.pos.x + hitbox.top.x + velo.x) / ASSET] == c)
		return (0);
	if (data->map[(data->player.pos.y + hitbox.bot.y + velo.y) / ASSET][(data->player.pos.x + hitbox.top.x + velo.x) / ASSET] == c)
		return (0);
	if (data->map[(data->player.pos.y + hitbox.top.y + velo.y) / ASSET][(data->player.pos.x + hitbox.bot.x + velo.x) / ASSET] == c)
		return (0);
	if (data->map[(data->player.pos.y + hitbox.bot.y + velo.y) / ASSET][(data->player.pos.x + hitbox.bot.x + velo.x) / ASSET] == c)
		return (0);
    return (1);
}

char	remove_obj(t_data *data, t_hitbox hitbox, char c)
{
	t_vect	pos;

	pos = (t_vect){data->player.pos.x, data->player.pos.y};
	if (data->map[(pos.y + hitbox.top.y) / ASSET][(pos.x + hitbox.top.x) / ASSET] == c)
		return (data->map[(pos.y + hitbox.top.y) / ASSET]\
		[(pos.x + hitbox.top.x) / ASSET] = c - 32);
	if (data->map[(pos.y + hitbox.bot.y) / ASSET][(pos.x + hitbox.top.x) / ASSET] == c)
		return (data->map[(pos.y + hitbox.bot.y) / ASSET]\
		[(pos.x + hitbox.top.x) / ASSET] = c - 32);
	if (data->map[(pos.y + hitbox.top.y) / ASSET][(pos.x + hitbox.bot.x) / ASSET] == c)
		return (data->map[(pos.y + hitbox.top.y) / ASSET]\
		[(pos.x + hitbox.bot.x) / ASSET] = c - 32);
	if (data->map[(pos.y + hitbox.bot.y) / ASSET][(pos.x + hitbox.bot.x) / ASSET] == c)
		return (data->map[(pos.y + hitbox.bot.y) / ASSET]\
		[(pos.x + hitbox.bot.x) / ASSET] = c - 32);
	return (0);
}

static void	check_pos(t_data *data)
{
	int	x;
	int	y;

	x = data->player.pos.x / ASSET;
	y = data->player.pos.y / ASSET;
	if (remove_obj(data, data->player.hitbox, 'c'))
		data->engine.obj--;
	if (data->engine.obj == 0 && remove_obj(data, data->player.hitbox, 'e'))
		end_game(data);
}
// Movement function that checks for collisions before applying movement
void movement(t_data *data)
{
	data->player.velo.x += data->player.acc.x;
	data->player.velo.y += data->player.acc.y;
	if (data->player.velo.x > MAX_VELOCITY)
		data->player.velo.x = MAX_VELOCITY;
	if (data->player.velo.x < -MAX_VELOCITY)
		data->player.velo.x = -MAX_VELOCITY;
	if (data->player.velo.y > MAX_VELOCITY)
		data->player.velo.y = MAX_VELOCITY;
	if (data->player.velo.y < -MAX_VELOCITY)
		data->player.velo.y = -MAX_VELOCITY;
	if (data->player.acc.x == 0 && data->engine.jump == 0)
		data->player.velo.x *= FRICTION;
	if (data->player.acc.y == 0)
		data->player.acc.y = 1;
	data->player.hitbox.top = (t_vect) {10, 10};
	data->player.hitbox.bot = (t_vect) {54, 60};
	if (check_collision(data, data->player.hitbox, (t_vect) {data->player.velo.x, 0}, '1'))
		data->player.pos.x += data->player.velo.x;
	if (check_collision(data, data->player.hitbox, (t_vect) {0, data->player.velo.y}, '1'))
		data->player.pos.y += data->player.velo.y;
}

int	delta_time(t_data *data, struct timeval *time, int threshold)
{
	int				delta;
	struct timeval	new_time;

	if (gettimeofday(&new_time, NULL) == -1)
		clean_exit(data, 1);
	if (time->tv_usec < new_time.tv_usec)
		delta = new_time.tv_usec - time->tv_usec;
	else
		delta = 1000000 + new_time.tv_usec - time->tv_usec;
	if (delta >= threshold)
	{
		time->tv_usec = new_time.tv_usec;
		return (1);
	}
	return (0);
}

int	game_loop(t_data *data)
{
	if (data->engine.end == 0 && delta_time(data, &data->engine.time, 16667))
	{
		movement(data);
		step_count(data);
		world_init(data);
		check_pos(data);
	}
	return (1);
}
