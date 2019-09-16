/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:09:53 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/15 16:05:29 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/mman.h>
#include <unistd.h>

t_vector	*vector_init(t_vector *vec, size_t reserved_len)
{
	size_t		padd;

	vec->mem = reserved_len;
	vec->len = 0;
	reserved_len = reserved_len * sizeof(t_vected);
	if ((padd = getpagesize() - (reserved_len % getpagesize())) != 0)
		reserved_len += padd;
	if (!(vec->arr = mmap(NULL, reserved_len, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0)))
		return (NULL);
	return (vec);
}
