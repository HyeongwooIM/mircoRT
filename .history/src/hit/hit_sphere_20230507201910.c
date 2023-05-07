#include "structures.h"
#include "utils.h"

t_bool      hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec)
{
    t_vec3  oc; //방향벡터로 나타낸 구의 중심.
    //a, b, c는 각각 t에 관한 2차 방정식의 계수
    double  a;
    double  half_b;
    double  c;
    double  discriminant; //판별식
    double  sqrtd;
    double  root;

    oc = vminus(ray->orig, sp->center);
23  a = vlength2(ray->dir);
23  half_b = vdot(oc, ray->dir);
24  c = vlength2(oc) - sp->radius2;
26  discriminant = half_b * half_b - a * c;
27
28  if (discriminant < 0)
29      return (FALSE);
30  sqrtd = sqrt(discriminant);
31  //두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
32  root = (-half_b - sqrtd) / a;
33  if (root < rec->tmin || rec->tmax < root)
34  {
35      root = (-half_b + sqrtd) / a;
36      if (root < rec->tmin || rec->tmax < root)
37          return (FALSE);
38  }
39  rec->t = root;
40  rec->p = ray_at(ray, root);
41  rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius); // 정규화된 법선 벡터.
42  set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장.
43  return (TRUE);
}