#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include "../mlx/mlx.h"

typedef struct s_mlx		t_mlx;

# define EPSILON 0.001
# define WIDTH	800
# define HEIGHT	600

struct	s_mlx {
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
};

typedef struct s_scene
{
	t_camera		camera;
	t_object		*objects;
	t_object		*lights;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
}	t_scene;


#endif