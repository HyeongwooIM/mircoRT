#include "structure.h"

t_ray	ray_primary(t_camera *cam, int x, int y)
{
	t_ray	ray;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	ray_vec;

	ray.origin = cam->origin;
	horizontal = vmult(cam->right_normal, (double)x);
	vertical = vmult(cam->up_normal, (double)y);
	ray_vec = cam->left_bottom;
	ray_vec = vplus(ray_vec, horizontal);
	ray_vec = vplus(ray_vec, vertical);
	ray_vec = vminus(ray_vec, cam->origin);
	ray_vec = vunit(ray_vec);
	ray.dir = ray_vec;
	return (ray);
}
