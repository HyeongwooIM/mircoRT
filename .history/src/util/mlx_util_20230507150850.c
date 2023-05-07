#include "structure.h"

int	key_hook(int keycode, t_mlx *mlx)
{
	(void) mlx;
	if (keycode == 53)
		ft_exit(1);
	return (0);
}