/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:01:12 by secros            #+#    #+#             */
/*   Updated: 2025/02/26 09:19:20 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	set_input(int key, t_data *data)
{
	erease_cursor(data->load, data->mlx_info.w_size->x, \
	data->mlx_info.w_size->y);
	if (key == W_KEY)
		if (data->mlx_info.w_size->y > 66)
			data->mlx_info.w_size->y -= 100;
	if (key == S_KEY)
		if (data->mlx_info.w_size->y < 366)
			data->mlx_info.w_size->y += 100;
	change_selection(data);
	if (key == ENTER)
	{
		data->engine.set = data->mlx_info.w_size->y / 100;
		mlx_destroy_image(data->mlx_info.mlx, data->load->img);
		loading_screen(data, data->load);
	}
	if (key == ESCAPE)
	{
		mlx_destroy_image(data->mlx_info.mlx, data->load->img);
		loading_screen(data, data->load);
	}
	return (0);
}

static void	setting(t_data *data, t_pict *load)
{
	int		x[2];

	data->load = load;
	mlx_destroy_image(data->mlx_info.mlx, data->load->img);
	load->img = mlx_xpm_file_to_image(data->mlx_info.mlx, \
	"./sprite/settings.xpm", &x[1], &x[0]);
	if (!load->img)
		confirm(data, 1);
	load->addr = mlx_get_data_addr(load->img, &load->bytes, \
	&load->l_len, &load->endian);
	data->mlx_info.w_size->x = 30;
	change_resolution(data);
	draw_cursor(load, 30, data->mlx_info.w_size->y);
	mlx_put_image_to_window(data->mlx_info.mlx, \
	data->mlx_info.win, load->img, 0, 0);
	mlx_hook(data->mlx_info.win, DestroyNotify, 0, quit, data);
	mlx_hook(data->mlx_info.win, KeyPress, KeyPressMask, set_input, data);
}

int	confirm(t_data *data, int error)
{
	if (data->mlx_info.w_size->y == 390 || error == 1)
	{
		if (data->load->img)
			mlx_destroy_image(data->mlx_info.mlx, data->load->img);
		mlx_destroy_window(data->mlx_info.mlx, data->mlx_info.win);
		mlx_destroy_display(data->mlx_info.mlx);
		free(data->mlx_info.mlx);
		free_the_mallocs(data->map);
		exit(error);
	}
	if (data->mlx_info.w_size->y == 265)
		setting(data, data->load);
	if (data->mlx_info.w_size->y == 110)
	{
		mlx_loop_end(data->mlx_info.mlx);
		mlx_destroy_image(data->mlx_info.mlx, data->load->img);
		mlx_destroy_window(data->mlx_info.mlx, data->mlx_info.win);
		mlx_destroy_display(data->mlx_info.mlx);
		free(data->mlx_info.mlx);
		launch(data);
	}
	return (0);
}

static int	load_input(int key, t_data *data)
{
	erease_cursor(data->load, data->mlx_info.w_size->x, \
	data->mlx_info.w_size->y);
	if (key == W_KEY)
	{
		if (data->mlx_info.w_size->y == 390)
			data->mlx_info.w_size->y = 265;
		else if (data->mlx_info.w_size->y == 265)
			data->mlx_info.w_size->y = 110;
	}
	if (key == S_KEY)
	{
		if (data->mlx_info.w_size->y == 110)
			data->mlx_info.w_size->y = 265;
		else if (data->mlx_info.w_size->y == 265)
			data->mlx_info.w_size->y = 390;
	}
	change_selection(data);
	if (key == ENTER)
		confirm(data, 0);
	if (key == ESCAPE)
	{
		data->mlx_info.w_size->y = 390;
		confirm(data, 0);
	}
	return (0);
}

void	loading_screen(t_data *data, t_pict *load)
{
	int		x[2];

	data->engine.set = LOW;
	data->load = load;
	load->img = mlx_xpm_file_to_image(data->mlx_info.mlx, \
	"./sprite/loading.xpm", &x[1], &x[0]);
	if (!load->img)
		confirm(data, 1);
	load->addr = mlx_get_data_addr(load->img, \
	&load->bytes, &load->l_len, &load->endian);
	draw_cursor(load, 30, 110);
	data->mlx_info.w_size->x = 30;
	data->mlx_info.w_size->y = 110;
	mlx_put_image_to_window(data->mlx_info.mlx, \
	data->mlx_info.win, load->img, 0, 0);
	mlx_hook(data->mlx_info.win, DestroyNotify, 0, quit, data);
	mlx_hook(data->mlx_info.win, KeyPress, KeyPressMask, load_input, data);
	mlx_loop(data->mlx_info.mlx);
}
