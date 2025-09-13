/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pol <pol@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:41:36 by pol               #+#    #+#             */
/*   Updated: 2025/09/13 12:43:34 by pol              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Description: Mini test cub3D - MLX + libft (ft_strlen)                   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>     // write
#include "mlx.h"
#include "libft.h"      // Assure-toi que -Ilibft/includes est bien dans ton Makefile

#define WIDTH   800
#define HEIGHT  600

// Keycodes cross-platform (macOS vs Linux/X11)
#ifdef __APPLE__
# define KEY_ESC 53
# define EVENT_DESTROY 17
#else
# include <X11/keysym.h>
# define KEY_ESC XK_Escape
# define EVENT_DESTROY 17
#endif

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_app
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_app;

static void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	render_gradient(t_img *img)
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			// petit dégradé simple : R = x, G = y, B = x^y
			int r = (x * 255) / (WIDTH - 1);
			int g = (y * 255) / (HEIGHT - 1);
			int b = (x ^ y) & 0xFF;
			int color = (r << 16) | (g << 8) | b;
			pixel_put(img, x, y, color);
		}
	}
}

static int	on_key(int keycode, t_app *app)
{
	if (keycode == KEY_ESC)
	{
		if (app->win)
			mlx_destroy_window(app->mlx, app->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

static int	on_close(t_app *app)
{
	(void)app;
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(void)
{
	t_app		app;
	const char	*msg = "Hello from libft (ft_strlen) — if you read this, libft is linked!";

	// Petit test libft: on affiche avec write() mais la longueur vient de ft_strlen
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	write(STDOUT_FILENO, "\n", 1);

	app.mlx = mlx_init();
	if (!app.mlx)
		return (write(2, "mlx_init failed\n", 16), EXIT_FAILURE);

	app.win = mlx_new_window(app.mlx, WIDTH, HEIGHT, "cub3D — MLX test");
	if (!app.win)
		return (write(2, "mlx_new_window failed\n", 22), EXIT_FAILURE);

	app.img.img = mlx_new_image(app.mlx, WIDTH, HEIGHT);
	if (!app.img.img)
		return (write(2, "mlx_new_image failed\n", 21), EXIT_FAILURE);

	app.img.addr = mlx_get_data_addr(app.img.img, &app.img.bpp, &app.img.line_len, &app.img.endian);

	// Rendu d’un dégradé pour tester l’image
	render_gradient(&app.img);

	// Affiche l’image en (0,0)
	mlx_put_image_to_window(app.mlx, app.win, app.img.img, 0, 0);

	// Hooks: ESC + bouton de fermeture fenêtre
	mlx_key_hook(app.win, (int (*)(int, void *))on_key, &app);
	mlx_hook(app.win, EVENT_DESTROY, 0, (int (*)(void *))on_close, &app);

	mlx_loop(app.mlx);
	return (0);
}
