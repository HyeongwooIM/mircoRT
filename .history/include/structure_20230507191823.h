#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include "../mlx/mlx.h"

typedef struct s_mlx		t_mlx;
typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;
typedef struct s_camera		t_camera;
typedef struct s_object		t_object;
typedef struct s_ambient	t_ambient;
typedef struct s_hit_record	t_hit_record;
typedef struct s_scene		t_scene;
typedef int					t_bool;
typedef int					t_object_type;

# define FALSE 0
# define TRUE 1
# define SP 0
# define PL 1
# define CY 2
# define LIGHT_POINT 3

# define EPSILON 0.001
# define WIDTH	800
# define HEIGHT	600




struct s_vec3
{
	double			x;
	double			y;
	double			z;
};

struct	s_mlx {
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
};

struct s_ambient
{
	t_color3		light_color;
	double			bright_ratio;
};

struct	s_camera
{
	t_point3    origin;  // 카메라 원점(위치)
	t_vec3      dir; // 카메라 벡터
  t_vec3      right_normal; // 카메라 벡터가 평면이 아닐 때의 left_bottom을 구하기 위해 
  t_vec3      up_normal; // 카메라 벡터가 평면이 아닐 때의 left_bottom을 구하기 위해 
	t_point3		left_bottom;
	double      fov;       // 화각
	double      focal_len; // 화각에 따라 카메라와 viewport와의 거리가 달라진다.
};

struct s_hit_record
{
    t_point3    p; // 교점(충돌 지점)에 대한 좌표.
    t_vec3       normal; // 교점에서 뻗어나온 법선(단위 벡터)
    double      tmin; // 기본 0, 물체가 뒤에 있을 경우에는 감지하지 않는다.
    double      tmax; // 광선의 가시거리, 일정 거리를 벗어나면 감지하지 않는다.
    double      t; // 광선의 원점과 교점 사이의 거리.
    t_bool      front_face;
	t_color3	color;
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
	t_ambient		ambient;
	t_ray			ray;
	t_hit_record	rec;
}	t_scene;


#endif