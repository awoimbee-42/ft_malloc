/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:33:38 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/16 18:59:27 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intrin_malloc.h"

/*
**	returns 0 on success
*/

int			get_idx(const void *ptr, const t_bin *b, int *i, size_t *map_size)
{
	if (((b->used & sml_bin()))
		&& (void*)b->mem <= ptr
		&& ptr < sml_bin_end(b))
	{
		DBG_PRINT("FREE SMALL BIN PIECE OF SHIT", NULL);
		*i = ((uintptr_t)ptr - (uintptr_t)&b->mem[0]) / g_bin.sml_elem_size;
		*map_size = g_bin.sml_map_size;
		return (0);
	}
	else if (((b->used & med_bin()))
		&& (void*)b->mem <= ptr
		&& ptr < med_bin_end(b))
	{
		DBG_PRINT("FREE MED BIN", NULL);
		*i = ((uintptr_t)ptr - (uintptr_t)&b->mem[0]) / g_bin.med_elem_size;
		*map_size = g_bin.med_map_size;
		return (0);
	}
	return (1);
}

void		rm_bin(t_bin *b[2], size_t map_size)
{
	b[1]->next = b[0]->next;
	munmap(b[0], map_size);
}

void		free_mut(void *ptr)
{
	t_bin		*b[2];
	size_t		map_size;
	int			idx;

	b[0] = (t_bin*)&g_bin;
	while ((b[1] = b[0])
		&& (b[0] = b[0]->next))
	{
		if (get_idx(ptr, b[0], &idx, &map_size))
		{
			if ((b[0]->used & big_bin()) && b[0]->mem == ptr)
			{
				DBG_PRINT("FREE BIG BOI", NULL);
				rm_bin(b, b[0]->used & ~big_bin());
				return ;
			}
			continue;
		}
		if (!(b[0]->used & (get1() << idx)))
			ERR_PRINT("POINTER ALREADY FREE-ED %lx", ptr);
		b[0]->used &= ~(get1() << idx);
		if ((b[0]->used & ~any_bin()) == 0)
			rm_bin(b, map_size);
		return ;
	}
	ERR_PRINT("free: unknown pointer %p", ptr);
	return ;
}

void		free(void *ptr)
{
	if (ptr == NULL)
		return ;
	pthread_mutex_lock(&g_bin.lock);
	init();
	free_mut(ptr);
	pthread_mutex_unlock(&g_bin.lock);
}
