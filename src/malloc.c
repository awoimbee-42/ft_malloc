/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:43:51 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/03 02:51:13 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

t_malloc	g_malloc;

void			err(void)
{
	fputs("Fuck", stdout);
	*(uint64_t*)(void*)79 = 9;
}

void			*mmap_malloc(size_t size)
{
	void	*ptr;

	ptr = mmap(
		NULL, size, PROT_WRITE | PROT_READ,
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		err();
	return (ptr);
}

void			init(void)
{
	size_t		page_size;

	pthread_mutex_init(&g_malloc.lock, NULL); // ???
	pthread_mutex_lock(&g_malloc.lock);
	page_size = getpagesize();
	g_malloc.sml_map_size = page_size * SML_PAGE_NB;
	g_malloc.sml_elem_size = (page_size * SML_PAGE_NB - sizeof(t_bin))
		/ BIN_SIZE;
	g_malloc.sml_elem_size -= g_malloc.sml_elem_size % ALIGNMENT;
	g_malloc.med_map_size = page_size * MED_PAGE_NB;
	g_malloc.med_elem_size = (page_size * MED_PAGE_NB - sizeof(t_bin))
		/ BIN_SIZE;
	g_malloc.med_elem_size -= g_malloc.sml_elem_size % ALIGNMENT;
	pthread_mutex_unlock(&g_malloc.lock);
}

uint			bin_empty_spot(const t_uint128 bfield)
{
	uint	spot;

	spot = 0;
	while (((bfield >> spot) & 1) == 1 && spot < 101)
		spot++;
	return (spot);
}

void			*malloc_sml(void)
{
	t_bin		*b;
	uint		spot;

	b = (t_bin*)&g_malloc;
	while (1)
	{
		if (b->used & SML_BIN && (spot = bin_empty_spot(b->used)) < BIN_SIZE)
		{
			b->used |= ((t_uint128)1) << spot;
			return (b->mem + g_malloc.sml_elem_size * spot);
		}
		if (!b->next)
		{
			b->next = mmap_malloc(g_malloc.sml_map_size);
			b->next->used = SML_BIN;
			b->next->next = NULL;
		}
		b = b->next;
	}
}

void			*malloc_med(void)
{
	t_bin		*b;
	uint		spot;

	b = (t_bin*)&g_malloc;
	while (1)
	{
		if (b->used & MED_BIN && (spot = bin_empty_spot(b->used)) < BIN_SIZE)
		{
			b->used |= ((t_uint128)1) << spot;
			return (b->mem + g_malloc.med_elem_size * spot);
		}
		if (!b->next)
		{
			b->next = mmap_malloc(g_malloc.med_map_size);
			b->next->used = MED_BIN;
			b->next->next = NULL;
		}
		b = b->next;
	}
}

void			*malloc_big(size_t size)
{
	size_t		page_size;
	size_t		alloc_size;
	t_bin		*b;

	page_size = getpagesize();
	alloc_size = size + sizeof(t_bin);
	alloc_size += page_size - (alloc_size % page_size);
	b = (t_bin*)&g_malloc;
	while (b->next)
		b = b->next;
	b->next = mmap_malloc(alloc_size);
	b = b->next;
	b->next = NULL;
	b->used = alloc_size;
	b->used |= BIG_BIN;
	DBG_PRINT("BIG stored size: %d, requested size: %d", alloc_size, size);
	return (&b->mem[0]);
}

void			*malloc(size_t size)
{
	DBG_PRINT("malloc called: %lu", size);
	if (g_malloc.sml_elem_size == 0)
		init();
	if (size <= g_malloc.sml_elem_size)
		return (malloc_sml());
	else if (size <= g_malloc.med_elem_size)
		return (malloc_med());
	else
		return (malloc_big(size));
}

void			print_allocs(void)
{
	t_bin		*b;

	b = g_malloc.bins;
	while (b)
	{
		printf("\tbin\n");
		b = b->next;
	}
}
