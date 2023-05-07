#include "structure.h"
#include "mlx_util.h"

int	key_hook(int keycode, t_mlx *mlx)
{
	(void) mlx;
	if (keycode == 53)
		ft_exit(1);
	return (0);
}

int	red_button(int key_num, t_mlx *mlx)
{
	(void)key_num;
	(void)mlx;
	ft_exit(1);
	return (0);
}