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

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direct;
}	t_ray;

struct s_light
{
	t_point3		origin;
	t_color3		light_color;
	double			bright_ratio;
};

struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
	t_color3		color;
};

struct	s_sphere
{
	t_point3		center;
	double			diameter;
	double			radius2;
};

typedef struct s_scene
{
	t_camera		camera;
	t_object		*world;
	t_object		*lights;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
}	t_scene;


#endif