/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:34:51 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/03 00:05:39 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*realloc(void *ptr, size_t size)
{
	for (t_bin *b = g_malloc.bins; b != NULL; b = b->next)
	{
		const uintptr_t		uptr = (uintptr_t)ptr;
		const uintptr_t		ubin = (uintptr_t)b;

		if (b->used & BIG_BIN) {
			const size_t alloc_size = (b->used & ~BIG_BIN) - sizeof(t_bin);
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
		else {
			size_t map_size;
			size_t elem_size;
			if (b->used & SML_BIN) {
				map_size = g_malloc.sml_map_size;
				elem_size = g_malloc.sml_elem_size;
			}
			else {
				map_size = g_malloc.med_map_size;
				elem_size = g_malloc.med_elem_size;
			}


			if (ubin < uptr && uptr < (ubin + map_size))
			{
				if (size <= elem_size) {
					return (ptr);
				}
				uint index = (uptr - (uintptr_t)&b->mem[0]) / elem_size;
				void* nw_ptr = malloc(size);
				if (nw_ptr == NULL) {
					DBG_PRINT("FAILED !\n", NULL);
					return (NULL);
				}
				memcpy(nw_ptr, ptr, elem_size);
				b->used &= !((t_uint128)1 << index);

				return (nw_ptr);
			}
		}
	}
	DBG_PRINT("Realloc: unknown pointer\n", NULL);
	return (NULL);
}
