/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:38:55 by secros            #+#    #+#             */
/*   Updated: 2025/02/26 05:17:23 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "so_long.h"
#include "fcntl.h"

static char	**new_line(char **map, char *str, int count)
{
	char	**new;
	size_t	i;

	i = 0;
	new = malloc(sizeof(char *) * (count + 1));
	if (!new)
		return (free_the_mallocs(map), NULL);
	if (!map)
	{
		new[0] = str;
		new[1] = NULL;
		return (new);
	}
	while (map[i])
	{
		new[i] = map[i];
		i++;
	}
	new[i] = str;
	new[count] = NULL;
	return (free(map), new);
}

static char	**read_map(int fd)
{
	char	*str;
	char	**map;
	size_t	count;

	count = 1;
	str = get_next_line(fd);
	if (!str)
		return (0);
	map = NULL;
	while (str)
	{
		map = new_line(map, str, count);
		if (!map)
			return (free(str), NULL);
		str = get_next_line(fd);
		count++;
	}
	return (map);
}

static int	check_condition(t_data *data, char *path)
{
	int		fd;
	char	*ext_check;
	char	**map;

	fd = open(path, O_RDONLY);
	ext_check = ft_strnstr(path, ".ber", ft_strlen(path));
	if (!ext_check || ext_check[4] != '\0')
		return (5);
	map = read_map(fd);
	if (fd > 0)
		close(fd);
	if (!map)
		return (1);
	if (check_map(map))
		return (free_the_mallocs(map), 2);
	if (check_data(data, map))
		return (free_the_mallocs(map), 3);
	if (all_access(data, map))
		return (free_the_mallocs(map), 4);
	data->map = map;
	return (0);
}

int	map_parsing(t_data *data, char *path)
{
	int	error;

	data->player.pos.x = 0;
	data->player.pos.y = 0;
	error = check_condition(data, path);
	if (error)
	{
		write(2, "Error\n", 6);
		if (error == 1)
			write(2, "Failed to load map\n", 19);
		if (error == 2)
			write(2, "Map has invalid format\n", 23);
		if (error == 3)
			write(2, "Map has invalid data\n", 21);
		if (error == 4)
			write(2, "Map has invalid pathing\n", 24);
		if (error == 5)
			write(2, "Map has invalid extention\n", 26);
		return (1);
	}
	return (0);
}
