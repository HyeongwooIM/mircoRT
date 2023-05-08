#include "structures.h"
#include "utils.h"
#include "trace.h"

// u : 광선의 방향 벡터
// o : 원기둥의 방향 벡터
// delta_P : 광선의 원점 - 원기둥의 중심점
// A : u와 o를 외적한 벡터의 제곱
// B : u와 o의 외적한 벡터와 delta_P와 o의 외적한 벡터를 내적
// C : delta_P와 o의 외적한 벡터의 제곱 - r(원의 반지름)의 제곱


int	cy_boundary(t_cylinder *cy, t_vec3 at_point, t_cylinops *c)
{
	double	hit_height;
	double	max_height;

	hit_height = vdot(vminus(at_point, cy->center), cy->dir);
	max_height = cy->height / 2;
	c->hit_height = hit_height;
	if (fabs(c->hit_height) > max_height)
		return (0);
	return (1);
}

t_vec3	get_cylinder_normal(t_cylinder *cy, t_vec3 at_point, double hit_height)
{
	t_point3	hit_center;
	t_vec3		normal;

	hit_center = vplus(cy->center, vmult(cy->dir, hit_height));
	normal = vminus(at_point, hit_center);
	return (vunit(normal));
}

int	hit_cylinder_cap(t_object *cy_obj, t_ray *ray,
	t_hit_record *rec, double height)
{
	t_cylinder	*cy;
	t_vec3		circle_center;
	double		r;
	float		root;

	cy = cy_obj->element;
	r = cy->diameter / 2;
	circle_center = vplus(cy->center, vmult(cy->dir, height));
	root = vdot(vminus(circle_center, ray->orig), cy->dir) \
		/ vdot(ray->dir, cy->dir);
	if (fabs(r) < fabs(vlength(vminus(circle_center, ray_at(ray, root)))))
		return (0);
	if (root < rec->tmin || rec->tmax < root)
		return (0);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->tmax = rec->t;
	if (0 < height)
		rec->normal = cy->dir;
	else
		rec->normal = vmult(cy->dir, -1);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (1);
}

int	hit_cylinder_value_setter(t_cylinops *c,
	t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	c->cy = cy_obj->element;
	c->u = ray->dir;
	c->o = c->cy->dir;
	c->r = c->cy->diameter / 2;
	c->delta_p = vminus(ray->orig, c->cy->center);
	c->a = vlength2(vcross(c->u, c->o));
	c->half_b = vdot(vcross(c->u, c->o), vcross(c->delta_p, c->o));
	c->c = vlength2(vcross(c->delta_p, c->o)) - pow(c->r, 2);
	c->discriminant = c->half_b * c->half_b - c->a * c->c;
	if (c->discriminant < 0)
		return (0);
	c->sqrtd = sqrt(c->discriminant);
	c->root = (-c->half_b - c->sqrtd) / c->a;
	if (c->root < rec->tmin || rec->tmax < c->root)
	{
		c->root = (-c->half_b + c->sqrtd) / c->a;
		if (c->root < rec->tmin || rec->tmax < c->root)
			return (0);
	}
	return (cy_boundary(c->cy, ray_at(ray, c->root), c));
}

int	hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinops	cylinder_ops;

	cylinder_ops.cy = 0;
	if (!hit_cylinder_value_setter(&cylinder_ops, cy_obj, ray, rec))
		return (0);
	rec->t = cylinder_ops.root;
	rec->p = ray_at(ray, cylinder_ops.root);
	rec->normal = get_cylinder_normal(cylinder_ops.cy,
			rec->p, cylinder_ops.hit_height);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (1);
}

t_bool      hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
    t_cylinder *cy = cy_obj->element;
    int result;

    result = 0;
    result += hit_cylinder_cap(cy_obj, ray, rec, cy->height / 2);
    result += hit_cylinder_cap(cy_obj, ray, rec, -(cy->height / 2));
    result += hit_cylinder_side(cy_obj, ray, rec);
    return (result);
}
