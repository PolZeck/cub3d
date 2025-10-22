/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:01:14 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/22 10:58:09 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "runtime.h"
#include <unistd.h>

// void	print_map_debug(const t_config *cfg, int show_spaces)
// {
// 	for (int y = 0; y < cfg->map_h; ++y)
// 	{
// 		for (int x = 0; x < cfg->map_w; ++x)
// 		{
// 			char c = cfg->map[y][x];
// 			if (show_spaces && c == ' ')
// 				c = '.';              // visualiser le “vide / extérieur”
// 			write(1, &c, 1);
// 		}
// 		write(1, "\n", 1);
// 	}
// 	ft_printf("Map: %dx%d | Player: (%d,%d,%c)\n",
// 		cfg->map_w, cfg->map_h, cfg->player_x, cfg->player_y, cfg->player_dir);
// }

int	main(int ac, char **av)
{
	t_config	cfg;

	if (ac != 2)
		error_exit("Error\nUsage: ./cub3D <file.cub>");
	parse_config(av[1], &cfg);
	// Debug: pour vérifier la map avant d’entrer dans l’app
	// print_map_debug(&cfg, 1, 1);
	run_app(&cfg);
	return (0);
}
