double	
decimal point(double base, int exponent)
{
	double	result;
	int		i;

	i = 1;
	result = 1;
	while (i <= exponent)
	{
		result = result * base;
		i++;
	}
	return (result);
}

double	ft_atof(char *src)
{
	int			i;
	int			sign;
	double		num;
	int			pointer;

	i = 1;
	sign = 1;
	num = 0;
	pointer = 0;
	while (ft_isspace(*src))
		src++;
	while (*src)
	{
		if (*src == '-')
			sign = -1;
		else if (!pointer && ft_isdigit(*src))
			num = (num * 10) + (*src - '0');
		else if (*src == '.')
			pointer = 1;
		else if (pointer && ft_isdigit(*src))
			num = (*src - '0') * ft_pow(0.1, i++) + num;
		src++;
	}
	return (sign * num);
}