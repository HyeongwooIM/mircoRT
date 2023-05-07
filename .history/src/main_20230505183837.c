#include "../mlx/mlx.h"

int main(int argc, char **argv)
{
	t_scene	*scene;
	t_mlx	mlx;

	if (argc == 1)
	{
		error_disposal("Error\n No Argument");
		return (-1);
	}
	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!(scene))
		return (-1);
	scene->world = NULL;
	scene->light = NULL;
	rt_finder(argc, argv);
	scene_value_setter(scene, argv[1]);
	init_camera(&scene->camera);
	mlx_initialize(&mlx);
	raytracing(scene, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
}