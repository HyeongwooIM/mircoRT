#include "../mlx/mlx.h"

void	scene_value_setter(t_scene *scene, char *input)
{
	int				fd;
	int				ret;
	char			*str;
	t_input_checker	input_checker;

	ret = 1;
	str = 0;
	fd = file_open(input);
	input_checker_init(&input_checker);
	while (ret != 0)
	{
		ret = ft_get_next_line(fd, &str);
		if (ret < 0)
			error_disposal("ERROR\n");
		space_converter(str);
		environment_value_setter(scene, str, &input_checker);
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

void ft_execute()
{

}

int main()
{
	ft_execute();
	return ();
}