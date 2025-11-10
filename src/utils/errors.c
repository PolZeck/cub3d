/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:00:42 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/10 17:07:57 by pledieu          ###   ########.fr       */
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
	on_close(app);
	if (msg)
		ft_putendl_fd((char *)msg, 2);
	exit(EXIT_FAILURE);
}
