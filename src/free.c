/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:33:38 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/03 02:36:32 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Norme de MERDE
*/

static inline t_uint128	get1(void)
{
	return (1);
}

static inline bool		free_big(void *ptr, t_bin **b)
{
	if ((b[0]->used & BIG_BIN) == 0 || &b[0]->mem[0] != ptr)
		return (false);
	DBG_PRINT("_free_big", NULL);
	b[1]->next = b[0]->next;
	munmap(b[0], b[0]->used & ~BIG_BIN);
	return (true);
}

static inline bool		free_med(void *ptr, t_bin **b)
{
	uintptr_t	i;

	if ((b[0]->used & MED_BIN) == 0)
		return (false);
	i = ((uintptr_t)ptr - (uintptr_t)&b[0]->mem[0]) / g_malloc.med_elem_size;
	if (i > 99)
		return (false);
	DBG_PRINT("_free_med", NULL);
	if (!(b[0]->used & (get1() << i)))
		ERR_PRINT("INVALID FREE %lx", ptr);
	b[0]->used &= ~(get1() << i);
	if ((b[0]->used & ~MED_BIN) == 0)
	{
		b[1]->next = b[0]->next;
		munmap(b[0], g_malloc.med_map_size);
	}
	return (true);
}

static inline bool		free_sml(void *ptr, t_bin **b)
{
	uintptr_t	i;

	if ((b[0]->used & SML_BIN) == 0)
		return (false);
	i = ((uintptr_t)ptr - (uintptr_t)&b[0]->mem[0]) / g_malloc.sml_elem_size;
	if (i > 99)
		return (false);
	DBG_PRINT("_free_sml", NULL);
	if (!(b[0]->used & (get1() << i)))
		ERR_PRINT("INVALID FREE %lx", ptr);
	b[0]->used &= ~(get1() << i);
	if ((b[0]->used & ~SML_BIN) == 0)
	{
		b[1]->next = b[0]->next;
		munmap(b[0], g_malloc.sml_map_size);
	}
	return (true);
}

void					free(void *ptr)
{
	t_bin		*b[2];

	if (ptr == NULL)
		return ;
	b[0] = (t_bin*)&g_malloc;
	b[1] = b[0];
	while ((b[0] = b[0]->next))
	{
		if (free_big(ptr, b) || free_med(ptr, b) || free_sml(ptr, b))
			return ;
		b[1] = b[0];
	}
	ERR_PRINT("free: unknown pointer %p", ptr);
	return ;
}
