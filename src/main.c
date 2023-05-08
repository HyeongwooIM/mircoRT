#include <stdio.h>
#include "structures.h"
#include "utils.h"
#include "print.h"
#include "scene.h"
#include "trace.h"
#include "../mlx/mlx.h"

typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_data		image;
}				t_vars;

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// esc key press event
int	key_hook(int keycode, t_mlx *mlx)
{
	if(keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}

t_scene *scene_init(void)
{
    t_scene     *scene;
    t_object    *world;
    t_object    *lights;
    double      ka; // 8.4 에서 설명

    // malloc 할당 실패 시, 실습에서는 return NULL로 해두었지만, 적절한 에러 처리가 필요하다.
    if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
        return (NULL);
    scene->canvas = canvas(WIDTH, HEIGHT);
    scene->camera = camera(&scene->canvas, point3(0, 0, 0));
    world = object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0)); // world 에 구1 추가
    oadd(&world, object(PL, sphere(point3(2, 0, -5), 100), color3(0, 0.5, 0))); // world 에 구2 추가
    oadd(&world, object(SP, sphere(point3(0, -1000, 0), 995), color3(1, 1, 1))); // world 에 구3 추가
    oadd(&world, object(CY, sphere(point3(3, 3, 3), 4), color3(0.3, 0.3, 0.3))); // world 에 구3 추가
    scene->world = world;
    lights = object(LIGHT_POINT, light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
    lights = object(LIGHT_POINT, light_point(point3(0, 20, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
    scene->light = lights;
    ka = 0.1; // 8.4 에서 설명
    scene->ambient = vmult(color3(1,1,1), ka); // 8.4 에서 설명
    return (scene);
}

int	main(void)
{
    int     i;
    int     j;
	double      u;
    double      v;
	t_color3    pixel_color;
    t_scene     *scene;
    t_mlx   mlx;
    // t_vars vars;
	// t_data image;


    //캔버스의 가로, 세로 픽셀값
    scene = scene_init();
    

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "miniRT"); 
  	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT); // 이미지 객체 생성
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian); // 이미지 주소 할당

    // 랜더링
    // P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
    // printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
    j = scene->canvas.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene->canvas.width)
        {
            u = (double)i / (scene->canvas.width - 1);
            v = (double)j / (scene->canvas.height - 1);
            //ray from camera origin to pixel
            scene->ray = ray_primary(&scene->camera, u, v);
            pixel_color = ray_color(scene);
            // ray_color함수의 인자도 ray, world를 모두 담고 있는 scene으로 바꿨다.
            // write_color(pixel_color);
            my_mlx_pixel_put(&mlx, i, HEIGHT - 1 - j, create_trgb(0, pixel_color.x * 255.999, pixel_color.y * 255.999, pixel_color.z * 255.999));
        ++i;
        }
    --j;
    }
    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.mlx);
    return (0);
}