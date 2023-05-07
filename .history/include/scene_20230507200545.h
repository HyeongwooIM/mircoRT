#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"

t_canvas    canvas(int  width, int height);
t_camera    camera(t_point3 orig, t_vec3 dir)
t_sphere    sphere(t_point3 center, double radius);

#endif