#include <stdio.h>

#include "structure.h"
#include "util.h"
#include "print.h"
#include "scene.h"
#include "trace.h"
#include "mlx.h"

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

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// esc key press event
int	key_hook(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	main(void)
{
    int     i;
    int     j;

    double      u;
    double      v;
    
    t_color3    pixel_color;
    t_canvas    canv;
    t_camera    cam;
    t_ray       ray;

    canv = canvas(600, 300);
    cam = camera(&canv, point3(0, 0, 0));

	t_vars vars;
	t_data image;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, canv.width, canv.height, "Hello miniRT!"); 
  	image.img = mlx_new_image(vars.mlx, canv.width, canv.height); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당

    printf("P3\n%d %d\n255\n", canv.width, canv.height);
    j = canv.height - 1;
    while (j >= 0)
    {
        i = 0;
       while (i < canv.width)
        {
            u = (double)i / (canv.width - 1);
            v = (double)j / (canv.height - 1);
            ray = ray_primary(&cam, u, v);
            pixel_color = ray_color(&ray);
            write_color(pixel_color);
			my_mlx_pixel_put(&image, i, canv.height - 1 - j, create_trgb(0, pixel_color.x * 255.999, pixel_color.y * 255.999, pixel_color.z * 255.999));
            ++i;
        }
        --j;
    }

	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);

    return (0);
}