/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:07:46 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/26 18:11:59 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_spaces(const char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return ((char *)s);
}

int	is_only_spaces(const char *s)
{
	while (*s == ' ' || *s == '\t' || *s == '\r')
		s++;
	return (*s == '\0');
}

int	is_header_line(const char *line)
{
	line = skip_spaces(line);
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2));
}