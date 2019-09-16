/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:16:55 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/16 15:35:33 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/mman.h>

t_vector	*vector_realloc(t_vector *vec)
{
	t_vected	*new_arr;
	size_t		new_mem_s;
	size_t		old_real_size;
	size_t		padd;


	vec->mem *= 2;
	new_mem_s = vec->mem * sizeof(t_vected);
	if ((padd = getpagesize() - (new_mem_s % getpagesize())) != 0)
		new_mem_s += padd;
	if (!(new_arr = mmap(NULL, new_mem_s, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0)))
		return (NULL);
	ft_memcpy(new_arr, vec->arr, vec->len * sizeof(t_vected));

	// free(vec->arr);
	vec->arr = new_arr;
	return (vec);



	size_t		padd;

	vec->mem = reserved_len;
	vec->len = 0;
	reserved_len = reserved_len * sizeof(t_vected);
	if ((padd = getpagesize() - (reserved_len % getpagesize())) != 0)
		reserved_len += padd;
	if (!(vec->arr = ))
		return (NULL);
	return (vec);
}
