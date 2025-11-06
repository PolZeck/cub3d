/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:08:44 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/06 15:39:09 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

int	map_w(const t_app *a)
{
	return (a->cfg.map_w);
}

int	map_h(const t_app *a)
{
	return (a->cfg.map_h);
}

char	map_at(const t_app *a, int y, int x)
{
	return (a->cfg.map[y][x]);
}
