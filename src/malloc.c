/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:43:51 by awoimbee          #+#    #+#             */
/*   Updated: 2020/09/10 01:18:14 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intrin_malloc.h"
#include <stdio.h>

t_malloc	g_bin;

static void		*malloc_sml(void)
{
	t_bin		*b;
	uint		spot;

	b = (t_bin*)&g_bin;
	while (1)
	{
		if (b->used & sml_bin() && (spot = bin_empty_spot(b->used)) < BIN_SIZE)
		{
			b->used |= get1() << spot;
			return (&b->mem[g_bin.sml_elem_size * spot]);
		}
		if (!b->next)
		{
			b->next = mmap_malloc(g_bin.sml_map_size);
			if (b->next == NULL)
				return (NULL);
			b->next->used = sml_bin();
			b->next->next = NULL;
		}
		b = b->next;
	}
}

static void		*malloc_med(void)
{
	t_bin		*b;
	uint		spot;

	b = (t_bin*)&g_bin;
	while (1)
	{
		if (b->used & med_bin() && (spot = bin_empty_spot(b->used)) < BIN_SIZE)
		{
			b->used |= get1() << spot;
			return (&b->mem[g_bin.med_elem_size * spot]);
		}
		if (!b->next)
		{
			b->next = mmap_malloc(g_bin.med_map_size);
			if (b->next == NULL)
				return (NULL);
			b->next->used = med_bin();
			b->next->next = NULL;
		}
		b = b->next;
	}
}

static void		*malloc_big(size_t size)
{
	size_t		page_size;
	size_t		alloc_size;
	t_bin		*b;

	page_size = getpagesize();
	alloc_size = size + sizeof(t_bin);
	alloc_size += page_size - (alloc_size % page_size);
	b = (t_bin*)&g_bin;
	while (b->next)
		b = b->next;
	b->next = mmap_malloc(alloc_size);
	if (b->next == NULL)
		return (NULL);
	b = b->next;
	b->next = NULL;
	b->used = alloc_size;
	b->used |= big_bin();
	DBG_PRINT("BIG stored size: %lu, requested size: %lu", alloc_size, size);
	return (&b->mem[0]);
}

void			*malloc_mut(size_t size)
{
	DBG_PRINT("malloc called: %lu", size);
	if (size <= g_bin.sml_elem_size)
		return (malloc_sml());
	else if (size <= g_bin.med_elem_size)
		return (malloc_med());
	return (malloc_big(size));
}

void __attribute__((visibility("default")))			*malloc(size_t size)
{
	void	*ret;

	if (size == 0)
		return (NULL);
	pthread_mutex_lock(&g_bin.lock);
	init();
	ret = malloc_mut(size);
	pthread_mutex_unlock(&g_bin.lock);
	DBG_PRINT("malloc called with size %lu returns %p", size, ret);
	return (ret);
}
