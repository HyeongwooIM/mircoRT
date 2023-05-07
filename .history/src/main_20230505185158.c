#include "../mlx/mlx.h"

static void set_v

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

void ft_execute()
{
	t_scene	*scene;
	t_mlx	mlx;


	raytracing(scene, &mlx);
}

int main()
{
	ft_execute();
	return ();
}