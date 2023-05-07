#include "util.h"
#include "structure.h"

double	vlength2(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double	vlength(t_vec3 vec)
{
	return (sqrt(vlength2(vec)));
}

t_vec3	vunit(t_vec3 vec)
{
	double	len;

	len = vlength(vec);
	if (len == 0)
	{
		ft_putstr_fd("Error\n:Devider is 0", 1);
		ft_exit(1);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}
