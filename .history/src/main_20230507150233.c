#include "../mlx/mlx.h"

static void	mlx_initialize(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img,
			&mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	mlx_key_hook(mlx->win, key_hook, &mlx);
	mlx_hook(mlx->win, 17, 0, red_button, &mlx);
}

static void ft_execute()
{
	t_mlx	mlx;

	mlx
}

int main ()
{
	ft_execute();
	return (1);
}