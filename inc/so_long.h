/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:25:05 by secros            #+#    #+#             */
/*   Updated: 2024/12/20 15:39:07 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// settings
# define DEFAULT_Y 2160
# define DEFAULT_X 3840
# define TITLE "So long"

// sprite
# define WALL "./sprite/wall.xpm"
# define WALL2 "./sprite/wall2.xpm"
# define PLAYER "./sprite/player.xpm"
# define OBJ "./sprite/obj.xpm"
# define CEXIT "./sprite/door.xpm"
# define TILE "./sprite/tile.xpm"
# define GATO "./sprite/end.xpm"

// key map
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define ESCAPE 65307

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
 typedef struct	s_pict
{
	void	*img;
	char	*addr;
	int		bytes;
	int		l_len;
	int		endian;
}			t_pict;

typedef struct	s_sprite
{
	t_pict	wall;
	t_pict	wall2;
	t_pict	tile;
	t_pict	obj;
	t_pict	play;
	t_pict	c_ex;
	t_pict	o_ex;
	t_pict	gato;
}			t_sprite;

typedef struct s_entity
{
	int				type;
	size_t			pos_x;
	size_t			pos_y;
	int				life;
	struct s_entity *next;
}				t_entity;

typedef struct s_data
{
	t_entity	player;
	void		*mlx;
	void		*win;
	t_sprite	sprite;
	int			exit;
	int			end;
	int			w_size[2];
	int			move;
	char		**map;
}		t_data;

//map_parsing
int	map_parsing(t_data *data, char *path);
int	check_map(char **map);
int	check_data(t_data *data, char **map);
int	all_access(t_data *data, char **map);

//input and moving
int	input(int key, void *param);
void	end_game(t_data *data);
int	clean_exit(t_data *data, int error);

//generate world
void	world_init(t_data *data);
void	draw_tiles(t_data *data, void *img, size_t x, size_t y);

#endif