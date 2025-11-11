/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:00:42 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 13:54:24 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "runtime.h"

void	error_exit(const char *msg)
{
	if (msg)
		ft_putendl_fd((char *)msg, 2);
	exit(EXIT_FAILURE);
}

void	error_exit_app(const char *msg, t_app *app)
{
	if (msg)
		ft_putendl_fd((char *)msg, 2);
	on_close(app);
	exit(EXIT_FAILURE);
}
