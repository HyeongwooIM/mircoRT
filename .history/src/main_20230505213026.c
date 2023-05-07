#include "../mlx/mlx.h"

static void add_value(t_scene *scene, char *input, t_input_checker input_checker)
{
	if (input[0] == 'A')
		ambient_value_setter(&scene->ambient, input);
	else if (input[0] == 'L')
		light_value_setter(&scene->light, input);
	else if (input[0] == 'C')
		camera_value_setter(&scene->camera, input);
	else if (input[0] == 's' && input[1] == 'p')
		sphere_value_setter(&scene->world, input);

	if (!check_valid_identifier(input))
		error_disposal("Error\n Invalid Identifier");
	if (input[0] == 'A')
	{
		input_checker->a_count++;
		ambient_value_setter(&scene->ambient, input);
	}
	else if (input[0] == 'C')
	{
		input_checker->c_count++;
		camera_value_setter(&scene->camera, input);
	}
	else if (input[0] == 'L')
	{
		input_checker->l_count++;
		light_value_setter(&scene->light, input);
	}
	else if (input[0] == 's' && input[1] == 'p')
		sphere_value_setter(&scene->world, input);
	else if (input[0] == 'p' && input[1] == 'l')
		plane_value_setter(&scene->world, input);
	else if (input[0] == 'c' && input[1] == 'y')
		cylinder_value_setter(&scene->world, input);
}
static void set_scene(t_scene *scene, char *input)
{
	int				fd;
	int				ret;
	char			*str;
	t_input_checker	input_checker;
	char			 **input;
	int				i;

	i = -1;
	ret = 1;
	str = 0;
	input_checker_init(&input_checker);
	while (ret != 0)
	{
		ret = input[++i];
		// ft_get_next_line(fd, &str);
		if (ret < 0)
			error_disposal("ERROR\n");
		space_converter(str);
		add_value(scene, input[i], &input_checker);
		if (input_checker.a_count > 1
			|| input_checker.c_count > 1 || input_checker.l_count > 1)
			error_disposal("Error\n Invalid Input");
		free(str);
		str = 0;
	}
	if (!input_checker.a_count
		|| !input_checker.c_count || !input_checker.l_count)
		error_disposal("Error\n Invalid Input");
}

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

	set_scene(scene);
	raytracing(scene, &mlx);
}

int main()
{
	ft_execute();
	return ();
}