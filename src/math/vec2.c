/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:58:26 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/06 15:58:29 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"

t_v2	v2(double x, double y)
{
	t_v2	r;

	r.x = x;
	r.y = y;
	return (r);
}

t_v2	v2_add(t_v2 a, t_v2 b)
{
	return (v2(a.x + b.x, a.y + b.y));
}

t_v2	v2_sub(t_v2 a, t_v2 b)
{
	return (v2(a.x - b.x, a.y - b.y));
}

t_v2	v2_scale(t_v2 a, double k)
{
	return (v2(a.x * k, a.y * k));
}
