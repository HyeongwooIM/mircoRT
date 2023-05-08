#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool      hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
    t_plane *pl = pl_obj->element;
    float numrator; // 판별식의 분자
    float denominator; // 판별식의 분모
    float root;
    denominator = vdot(ray->dir, pl->center);
    if (denominator < EPSILON) // 분모의 값이 0보다 작거나 같을 경우 충돌하지 않는다.
        return (FALSE);
    numrator = vdot(vminus(pl->dir, ray->orig), pl->center);
    root = numrator / denominator;
    if (root < rec->tmin || rec->tmax < root) 
        return (FALSE);
    rec->t = root;
    rec->p = ray_at(ray, root);    
    // rec->normal = pl->normal;
    rec->albedo = pl_obj->albedo;
    // print_vec(normal);
    return (TRUE);
}
