/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:00:53 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/15 13:01:02 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **tab)
{
	int i = 0;
	if (!tab) return;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_config(t_config *cfg)
{
	if (!cfg) return;
	free(cfg->tx.no);
	free(cfg->tx.so);
	free(cfg->tx.we);
	free(cfg->tx.ea);
	if (cfg->map)
	{
		for (int i = 0; i < cfg->map_h; ++i)
			free(cfg->map[i]);
		free(cfg->map);
	}
}
