/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:22:00 by secros            #+#    #+#             */
/*   Updated: 2025/02/26 14:19:19 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "ft_printf.h"

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