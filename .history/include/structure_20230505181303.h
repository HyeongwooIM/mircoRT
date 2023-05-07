#ifndef STRUCTURE_H
# define STRUCTURE_H



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