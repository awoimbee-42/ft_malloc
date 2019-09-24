/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:34:51 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/24 23:35:18 by awoimbee         ###   ########.fr       */
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
		const t_bin_info	bininf = g_inf.arr[bitfield_get_bin_size(b->used)];
		if (uptr > ubin && uptr < (ubin + bininf.map_size))
		{
			if (size < bininf.elem_size)
				return (ptr);
			uint index = (uptr - (uintptr_t)&b->mem[0]) / bininf.elem_size;
			void* nw_ptr = malloc(size);
			if (nw_ptr == NULL)
				{fprintf(stderr, "fuck you lol\n"); return (NULL);}
			memcpy(nw_ptr, ptr, bininf.elem_size);
			bitfield_unset_bit(&b->used, index);
			return (nw_ptr);
		}
	}
	fprintf(stderr, "Realloc: unknown pointer\n");
	return (NULL);
}
