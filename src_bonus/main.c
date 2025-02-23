/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:22:51 by secros            #+#    #+#             */
/*   Updated: 2025/02/23 17:56:09 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define TEST "./sprite/test.xpm"

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

int	main()
{
	t_data	data;
	t_pict	pt[3];
	int		i[2];
	t_vect pos = {0, 0};

	ft_bzero(&i, sizeof(int) * 2);
	data.mlx_info.mlx = mlx_init();
	data.mlx_info.win = mlx_new_window(data.mlx_info.mlx, 500, 500, "TEST");
	pt[0].img = mlx_new_image(data.mlx_info.mlx, 500, 500);
	pt[1].img = mlx_xpm_file_to_image(data.mlx_info.mlx, WALL, &i[0], &i[1]);
	pt[2].img = mlx_xpm_file_to_image(data.mlx_info.mlx, TEST, &i[0], &i[1]);
	pt[0].addr = mlx_get_data_addr(pt[0].img, &pt[0].bytes, &pt[0].l_len, &pt[0].endian);
	pt[2].addr = mlx_get_data_addr(pt[2].img, &pt[2].bytes, &pt[2].l_len, &pt[2].endian);
	pt[1].addr = mlx_get_data_addr(pt[1].img, &pt[1].bytes, &pt[1].l_len, &pt[1].endian);
	merge_image(pt[0], pt[1],pos);
	merge_image(pt[0], pt[2],pos);
	mlx_put_image_to_window(data.mlx_info.mlx, data.mlx_info.win, pt[0].img, 0, 0);
	mlx_loop(data.mlx_info.mlx);
}
