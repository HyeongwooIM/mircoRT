#include "../mlx/mlx.h"
#include "mlx_util.h"
#include "structure.h"

static void	raytracing(t_scene *scene, t_mlx *mlx)
{
	int			i;
	int			j;
	t_color3	pixel_color;

	j = HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < WIDTH)
		{
			scene->ray = ray_primary(&scene->camera, i, j);
			pixel_color = ray_color(scene);
			my_mlx_pixel_put(mlx, i, HEIGHT - 1 - j, \
			create_trgb(0, pixel_color.x, pixel_color.y, pixel_color.z));
			++i;
		}
		--j;
	}
}

static void	mlx_initialize(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img,
			&mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	mlx_key_hook(mlx->win, key_hook, &mlx);
	mlx_hook(mlx->win, 17, 0, red_button, &mlx);
}

static void ft_execute()
{
	t_mlx	mlx;

	mlx_initialize(&mlx);
	raytracing(scene, &mlx);
	mlx_loop(mlx.mlx);
}

int main ()
{
	ft_execute();
	return (1);
}