#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	t_bool		front_face;
	t_color3	color;
}	t_hit_record;

typedef struct s_ambient
{
	double		light_ratio;
	t_color3	light_color;
}	t_ambient;

typedef struct s_light
{
	t_point3	origin;
	double		bright_ratio;
}	t_light;

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
}	t_sphere;


typedef struct s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_obj_list		*objects;
	t_obj_list		*lights;
	t_ambient		ambient;
	t_ray			ray;
	t_hit_record	record;
}	t_scene;

#endif