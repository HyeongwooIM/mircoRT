#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;
typedef struct s_ray t_ray;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_sphere t_sphere;

typedef int             t_bool;
# define FALSE 0
# define TRUE 1

struct s_vec3
{
    double x;
    double y;
    double z;
};

struct  s_ray
{
    t_point3    orig;
    t_vec3      dir;
};

struct  s_camera
{
	t_point3    origin;  // 카메라 원점(위치)
	t_vec3      dir; // 카메라 벡터
    t_vec3      right_normal; // 카메라 벡터가 평면이 아닐 때의 left_bottom을 구하기 위해 
    t_vec3      up_normal; // 카메라 벡터가 평면이 아닐 때의 left_bottom을 구하기 위해 
	t_point3    left_bottom; // 왼쪽 아래 코너점

	double      fov;       // 화각
	double      focal_len; // 화각에 따라 카메라와 viewport와의 거리가 달라진다.
};

struct  s_canvas
{
    int     width; //canvas width
    int     height; //canvas height;
    double  aspect_ratio; //종횡비
};

struct  s_sphere
{
    t_point3    center;
    double      radius;
    double      radius2;
};


#endif