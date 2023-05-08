#include "trace.h"

t_bool          in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
    t_hit_record rec;

    rec.tmin = 0;
    rec.tmax = light_len;
    if (hit(objs, &light_ray, &rec))
        return (TRUE);
    return (FALSE);
}

t_vec3          reflect(t_vec3 v, t_vec3 n)
{
    double  ray_light_dot; // 교점에서 카메라로 향하는 벡터 v와 교점의 법선 벡터 N를 내적한 스칼라 값
    t_vec3  dot_vec;
    t_vec3  reverse_v; // 벡터 V를 반대방향으로 돌린 것, 역벡터
    
    ray_light_dot = vdot(v, n); // 벡터 V와 벡터 N를 내적한 값.
    dot_vec = vmult(n, ray_light_dot * 2);  // 내적한 값을 벡터화 시킨것 (벡터 N이 단위 벡터이기에 가능)
                                            // 2를 곱해주는 이유는 벡터 V를 역벡터화시켰기 때문.
    reverse_v = vmult(v, -1);    
    return (vplus(reverse_v, dot_vec));
}

t_color3        point_light_get(t_scene *scene, t_light *light)
{
    t_color3    diffuse; 
    t_vec3      light_dir; // 빛의 방향 벡터
    double      kd; // 난반사의 강도

    t_color3    specular; 
    t_vec3       view_dir; // 카메라 원점을 향하는 벡터 
    t_vec3       reflect_dir; // 법전을 기준으로 광선의 벡터를 대칭시킨 벡터
    double      spec; // 사이각의 크기에 따른 코사인 값
    double      ksn; // 반짝거리는 정도
    double      ks; // 

    light_dir = vunit(vminus(light->origin, scene->rec.p)); //교점에서 출발하여 광원을 향하는 벡터(정규화)
    // rec.p는 해당 광선(레이)가 뻗어나가면서 가장 먼저 마주친 물체의 교점에 대한 값이다.
    // cosΘ는 Θ 값이 90도 일 때 0이고 Θ가 둔각이 되면 음수가 되므로 0.0보다 작은 경우는 0.0으로 대체한다.
    kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);// (교점에서 출발하여 광원을 향하는 벡터)와 (교점에서의 법선벡터)의 내적값.
    // fmax 함수는 두 개의 인자 중 큰 값을 리턴한다. 만약 코사인세타가 둔각이 될 경우 음수가 되기에 0을 리턴하도록 한다.
    diffuse = vmult(light->light_color, kd);

    view_dir = vunit(vmult(scene->ray.dir, -1));
    reflect_dir = reflect(light_dir, scene->rec.normal);
    ksn = 30; // 작을 수록 정반사를 받는 범위는 늘어나지만 빛의 세기는 약해진다.
    ks = 0.8; // 정반사의 강도
    spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
    specular = vmult(vmult(light->light_color, ks), spec);
    
    return (vplus(diffuse, specular));
}   


t_color3        phong_lighting(t_scene *scene)
{
    t_color3    light_color;
    t_object    *lights;

    light_color = color3(0, 0, 0); //광원이 하나도 없다면, 빛의 양은 (0, 0, 0)일 것이다.
    lights = scene->light;
    while (lights) //여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular 값을 모두 구해줘야 한다
    {
        if(lights->type == LIGHT_POINT)
            light_color = vplus(light_color, point_light_get(scene, lights->element));
        lights = lights->next;
    }
    light_color = vplus(light_color, scene->ambient);
    return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
    //모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.
}