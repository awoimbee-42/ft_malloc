/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:34:51 by awoimbee          #+#    #+#             */
/*   Updated: 2020/04/30 11:27:49 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "op_bit.h"

void			*realloc(void *ptr, size_t size)
{
	for (t_bin *b = g_bins; b != NULL; b = b->next_bin)
	{
		const uintptr_t		uptr = (uintptr_t)ptr;
		const uintptr_t		ubin = (uintptr_t)b;
		const uint b_size = bitfield_get_bin_size(b->used);
		const t_bin_info	*bininf = &g_inf.arr[b_size];

		if (b_size == BIG) {
			const size_t alloc_size = bitfield_get_big_alloc_size(b->used) - sizeof(t_bin);
			if (ubin < uptr && uptr <= ubin + alloc_size) {
				if (alloc_size >= size) {
					return (ptr);
				}
				DBG_PRINT("Realloc a big boi\n", NULL);
				void* nw = malloc(size); // TODO
				if (!nw) {
					DBG_PRINT("BIG MALLOC FAILED\n", NULL);
					return NULL;
				}
				memcpy(nw, ptr, alloc_size);
				free(ptr);
				DBG_PRINT("ok big boi\n", NULL);
				return (nw);
			}
			continue;
		}

		if (ubin < uptr && uptr < (ubin + bininf->map_size))
		{
			if (size <= bininf->elem_size) {
				return (ptr);
			}
			uint index = (uptr - (uintptr_t)&b->mem[0]) / bininf->elem_size;
			void* nw_ptr = malloc(size);
			if (nw_ptr == NULL) {
				DBG_PRINT("FAILED !\n", NULL);
				return (NULL);
			}
			memcpy(nw_ptr, ptr, bininf->elem_size);
			bitfield_unset_bit(&b->used, index);
			return (nw_ptr);
		}
	}
	DBG_PRINT("Realloc: unknown pointer\n", NULL);
	return (NULL);
}
