/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:25:05 by secros            #+#    #+#             */
/*   Updated: 2025/02/23 10:20:06 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// settings
# define DEFAULT_Y 1080
# define DEFAULT_X 1920
# define TITLE "So long"

// sprite
# define WALL "./sprite/wall.xpm"
# define WALL2 "./sprite/wall2.xpm"
# define PLAYER "./sprite/play.xpm"
# define OBJ "./sprite/obj.xpm"
# define CEXIT "./sprite/door.xpm"
# define OEXIT "./sprite/door_o.xpm"
# define TILE "./sprite/tile.xpm"
# define END "./sprite/end.xpm"

// key map
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define ESCAPE 65307
# define ENTER 65293
# define SPACE 32

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include "ft_printf.h"

enum e_type
{
	PLAY,
	ENEMY,
};

enum e_render
{
	LOW,
	MEDIUM,
	HIGH,
	MAX,
};

typedef struct s_pict
{
	void	*img;
	char	*addr;
	int		bytes;
	int		l_len;
	int		endian;
}	t_pict;

typedef struct s_sprite
{
	t_pict	wall;
	t_pict	wall2;
	t_pict	tile;
	t_pict	obj;
	t_pict	play;
	t_pict	c_ex;
	t_pict	o_ex;
	t_pict	end;
}	t_sprite;

typedef struct s_vect
{
	int	x;
	int	y;
}	t_vect;

typedef struct s_entity
{
	int				type;
	t_vect			pos;
	int				life;
	struct s_entity	*next;
}	t_entity;

typedef struct s_engine
{
	int	key;
	int	jump;
	int	end;
	int	obj;
	int	move;
	int	set;
}	t_engine;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	size_t	w_size[2];
}	t_mlx;


typedef struct s_data
{
	t_entity	player;
	t_sprite	sprite;
	t_pict		*load;
	t_mlx		mlx_info;
	t_engine	engine;
	char		**map;
}		t_data;

//settings
void	loading_screen(t_data *data, t_pict *load);
int		launch(t_data *data);
void	load_asset(t_data *data);
int		confirm(t_data *data, int error);

//image and screen rendering
void	draw_cursor(t_pict *img, int x, int y);
void	resolution(t_data *data);
void	erease_cursor(t_pict *img, int x, int y);

//map_parsing
int		map_parsing(t_data *data, char *path);
int		check_map(char **map);
int		check_data(t_data *data, char **map);
int		all_access(t_data *data, char **map);

//input and moving
int		input(int key, void *param);
void	end_game(t_data *data);
int		clean_exit(t_data *data, int error);
int		close_button(t_data *data);
int		quit(t_data *data);

//generate world
int		rendering(t_data *param);
void	world_init(t_data *data);

#endif