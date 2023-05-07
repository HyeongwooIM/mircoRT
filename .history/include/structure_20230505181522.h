#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_obj_list
{
	t_obj_type	type;
	t_color3	color;
	void		*object;
	void		*next;
}	t_obj_list;


typedef struct s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
}	t_canvas;

typedef struct s_camera
{
	t_point3	origin;
	double		viewport_height;
	double		viewport_width;
	t_vec3		w_dir;
	t_vec3		u_dir;
	t_vec3		v_dir;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_point3	left_bottom;
}	t_camera;

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}	t_ray;


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