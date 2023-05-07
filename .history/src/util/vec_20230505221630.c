t_vec3	parse_vec(char *str)
{
	char	**info;
	t_vec3	vec;

	info = ft_split(str, ',');
	if (ft_get_count_of_list(info) != 3)
	{
		ft_putstr_fd("Format is not Valid", STDERR_FILENO);
		free_all(info);
		ft_exit(1);
	}
	vec.x = ft_atod(info[0]);
	vec.y = ft_atod(info[1]);
	vec.z = ft_atod(info[2]);
	free_all(info);
	return (vec);
}