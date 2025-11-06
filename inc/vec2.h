/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pol <pol@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 08:23:29 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/06 13:26:26 by pol              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
#define VEC2_H

typedef struct s_v2
{
	double x;
	double y;
} t_v2;

static inline t_v2 v2(double x, double y)
{
	t_v2 r = {x, y};
	return r;
}
static inline t_v2 v2_add(t_v2 a, t_v2 b) { return v2(a.x + b.x, a.y + b.y); }
static inline t_v2 v2_sub(t_v2 a, t_v2 b) { return v2(a.x - b.x, a.y - b.y); }
static inline t_v2 v2_scale(t_v2 a, double k) { return v2(a.x * k, a.y * k); }

#endif
