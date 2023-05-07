#include "mlx_util.h"
#include "structure.h"

int	key_hook(int keycode, t_mlx *mlx)
{
	(void) mlx;
	if (keycode == 53)
		exit(1);
	return (0);
}

int	red_button(int key_num, t_mlx *mlx)
{
	(void)key_num;
	(void)mlx;
	exit(1);
	return (0);
}