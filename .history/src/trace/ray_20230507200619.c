#include "trace.h"

//ray 생성자(정규화 된 ray)
t_ray       ray(t_point3 orig, t_vec3 dir)
{
    t_ray ray;

    ray.orig = orig;
    ray.dir = vunit(dir);
    return (ray);
}

//ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점.
t_point3    ray_at(t_ray *ray, double t)
{
    t_point3 at;

    at = vplus(ray->orig, vmult(ray->dir, t));
    return (at);
}
//primary_ray 생성자
t_ray       ray_primary(t_camera *cam, double u, double v)
{
    t_ray   ray;
    
    t_vec3  horizontal;
    t_vec3  vertical;
    t_point3   viewport_point;

    ray.orig = cam->orig; // 0, 0, 0

    horizontal = vmult(cam->right_normal, u);
    vertical = vmult(cam->up_normal, v);
    viewport_point = vplus(cam->left_bottom, horizontal);
    viewport_point = vplus(viewport_point, vertical);

    ray.dir = vunit(vminus(viewport_point, ray.orig));
    return (ray);
}

//광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴.
t_color3    ray_color(t_ray *ray, t_sphere *sphere)
{
	double  t;
	t_vec3  n;

    t = hit_sphere(sphere, ray);
    if (t > 0.0)
    {
        //정규화 된 구 표면에서의 법선
        n = vunit(vminus(ray_at(ray, t), sphere->center));
        return (vmult(color3(n.x + 1, n.y + 1, n.z + 1), 0.5));
    }
    else
    {
        //ray의 방향벡터의 y 값을 기준으로 그라데이션을 주기 위한 계수.
        t = 0.5 * (ray->dir.y + 1.0);
        // (1-t) * 흰색 + t * 하늘색
        return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0),     t)));
    }
}