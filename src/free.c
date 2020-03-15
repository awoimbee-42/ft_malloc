/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:33:38 by awoimbee          #+#    #+#             */
/*   Updated: 2019/10/11 20:55:26 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <op_bit.h>
#include <params.h>

void			free(void *ptr)
{
	const uintptr_t uptr = (uintptr_t)ptr;

	if(ptr == NULL)
		{DBG_PRINT("Free: NULL pointer\n", NULL); return;}
	for (t_bin *b = g_bins, *c = NULL; b != NULL; c = b, b = b->next_bin)
	{
		const uintptr_t	ubin = (uintptr_t)b;

		if (bitfield_get_bin_size(b->used) == BIG)
		{
			size_t bin_size = bitfield_get_big_alloc_size(b->used);
			if (uptr == ubin + sizeof(t_bin))
			{
				DBG_PRINT("Free: unset in %s bin (%p)\n",
					bin_size_name(bitfield_get_bin_size(b->used)),
					b
				);
				if (c)
					c->next_bin = b->next_bin;
				else
					g_bins = b->next_bin;
				munmap(ptr, bin_size);
				return ;
			}
		}
		else
		{
			const t_bin_info bininf = g_inf.arr[bitfield_get_bin_size(b->used)];
			if (uptr > ubin && uptr < (ubin + bininf.map_size))
			{
				uint index = (uptr - (uintptr_t)&b->mem[0]) / bininf.elem_size;
				bitfield_unset_bit(&b->used, index);
				DBG_PRINT("Free: unset in %s bin (%p), index %u\n",
					bin_size_name(bitfield_get_bin_size(b->used)),
					b,
					index
				);
				return ;
			}
		}


	}
	ERR_PRINT("free: unknown pointer %p\n", ptr);
	return ;
}
