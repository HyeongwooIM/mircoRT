#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"

void		init_camera(t_camera *cam);
t_object	*object(t_object_type type, void *element, t_color3 color);
t_light		*light_point(t_point3 light_origin,
				t_color3 light_color, double bright_ratio);
t_sphere	*sphere(t_point3 center, double diameter);
t_plane		*plane(t_point3 center, t_vec3 dir);
t_cylinder	*cylinder(t_point3 center, t_vec3 dir,
				float diameter, float height);
#endif