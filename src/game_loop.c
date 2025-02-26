/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:53:36 by secros            #+#    #+#             */
/*   Updated: 2025/02/26 08:08:13 by secros           ###   ########.fr       */
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

/* void	movement(t_data *data)
{
	data->player.velo.x += data->player.acc.x;
	data->player.velo.y += data->player.acc.y;
	if (data->player.velo.x > 10)
		data->player.velo.x = 10;
	if (data->player.velo.x < -10)
		data->player.velo.x = -10;
	if (data->player.velo.y > 10)
		data->player.velo.y = 10;
	if (data->player.velo.y < -10)
		data->player.velo.y = -10;
	if (data->player.acc.x == 0 && data->engine.jump == 0)
		data->player.velo.x /= 1.2;
	if (data->player.acc.y == 0)
		data->player.acc.y = 1;
	// if (data->map[data->player.pos.y / 64][(data->player.pos.x + data->player.velo.x) / 64] == '1')
	// 	return ;
	data->player.pos.x += data->player.velo.x;
	data->player.pos.y += data->player.velo.y;
	
}
 */


int check_collision(t_data *data, t_hitbox hitbox, t_vect velo, char c)
{
    // Horizontal check (left/right)

	if (velo.x != 0)
	{
		if (data->map[(data->player.pos.y + hitbox.top.y) / 64][(data->player.pos.x + hitbox.top.x + velo.x) / 64] == c)
			return (0);
		if (data->map[(data->player.pos.y + hitbox.bot.y) / 64][(data->player.pos.x + hitbox.top.x + velo.x) / 64] == c)
			return (0);
		if (data->map[(data->player.pos.y + hitbox.top.y) / 64][(data->player.pos.x + hitbox.bot.x + velo.x) / 64] == c)
			return (0);
		if (data->map[(data->player.pos.y + hitbox.bot.y) / 64][(data->player.pos.x + hitbox.bot.x + velo.x) / 64] == c)
			return (0);
	}
	if (velo.y != 0)
	{
		if (data->map[(data->player.pos.y + hitbox.top.y + velo.y) / 64][(data->player.pos.x + hitbox.top.x) / 64] == c) 
			return (0);
		if (data->map[(data->player.pos.y + hitbox.bot.y + velo.y) / 64][(data->player.pos.x + hitbox.bot.x) / 64] == c)
			return (0);
		if (data->map[(data->player.pos.y + hitbox.top.y + velo.y) / 64][(data->player.pos.x + hitbox.bot.x) / 64] == c) 
			return (0);
		if (data->map[(data->player.pos.y + hitbox.bot.y + velo.y) / 64][(data->player.pos.x + hitbox.top.x) / 64] == c)
			return (0);
	}
    return (1);
}

static void	check_pos(t_data *data)
{
	int	x;
	int	y;
	int	count;

	x = data->player.pos.x / 64;
	y = data->player.pos.y / 64;
	count = 0;
	if (data->map[y][x] == 'c' && !check_collision(data, data->player.hitobx, (t_vect){1, 1}, 'c'))
	{
		data->map[y][x] = 'C';
		data->engine.obj--;
	}
	else if (data->engine.obj == 0 && !check_collision(data, data->player.hitobx, (t_vect){1, 1}, 'e'))
		end_game(data);
}
// Movement function that checks for collisions before applying movement
void movement(t_data *data)
{
	data->player.velo.x += data->player.acc.x;
	data->player.velo.y += data->player.acc.y;
	if (data->player.velo.x > 10)
		data->player.velo.x = 10;
	if (data->player.velo.x < -10)
		data->player.velo.x = -10;
	if (data->player.velo.y > 10)
		data->player.velo.y = 10;
	if (data->player.velo.y < -10)
		data->player.velo.y = -10;
	if (data->player.acc.x == 0 && data->engine.jump == 0)
		data->player.velo.x *= 0.99;
	if (data->player.acc.y == 0)
		data->player.acc.y = 1;
	data->player.hitobx.top = (t_vect) {10, 10};
	data->player.hitobx.bot = (t_vect) {44, 60};
	if (check_collision(data, data->player.hitobx, (t_vect) {data->player.velo.x, 0}, '1'))
		data->player.pos.x += data->player.velo.x;
	if (check_collision(data, data->player.hitobx, (t_vect) {0, data->player.velo.y}, '1'))
		data->player.pos.y += data->player.velo.y;
}


int	game_loop(t_data *data)
{
	if (data->engine.end == 0)
	{
		movement(data);
		check_pos(data);
		step_count(data);
		world_init(data);
	}
	return (1);
}
