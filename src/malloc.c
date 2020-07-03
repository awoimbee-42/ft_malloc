/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:43:51 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/03 17:01:55 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

t_malloc	g_malloc;

void			err(void)
{
	ERR_PRINT("FUUUUUUUUUUUUUUUUUUUUUUUUUUUCK", NULL);
	*(uint64_t*)(void*)79 = 9;
}

void			*mmap_malloc(size_t size)
{
	void	*ptr;

	ptr = mmap(
		NULL, size, PROT_WRITE | PROT_READ,
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return NULL;
	return (ptr);
}

void			init(void)
{
	size_t		page_size;

	// pthread_mutex_init(&g_malloc.lock, NULL); // ???
	// pthread_mutex_trylock(&g_malloc.lock);
	page_size = getpagesize();
	g_malloc.sml_map_size = page_size * SML_PAGE_NB;
	g_malloc.sml_elem_size = (page_size * SML_PAGE_NB - sizeof(t_bin))
		/ BIN_SIZE;
	g_malloc.sml_elem_size -= g_malloc.sml_elem_size % ALIGNMENT;
	g_malloc.med_map_size = page_size * MED_PAGE_NB;
	g_malloc.med_elem_size = (page_size * MED_PAGE_NB - sizeof(t_bin))
		/ BIN_SIZE;
	g_malloc.med_elem_size -= g_malloc.sml_elem_size % ALIGNMENT;
	DBG_PRINT(
		"\n"
		"\tsml_elem_size: %1$9lu (%1$#9lx)\n"
		"\tmed_elem_size: %2$9lu (%2$#9lx)\n",
		g_malloc.sml_elem_size,
		g_malloc.med_elem_size);
}

void			free_all(void)
{
	t_bin	*b;
	t_bin	*b_next;
	char	*tmp;

	b = g_malloc.bins;
	while (b) {
		b_next = b->next;
		if (b->used & SML_BIN)
			munmap(b, g_malloc.sml_map_size);
		else if (b->used & MED_BIN)
			munmap(b, g_malloc.med_map_size);
		else
			munmap(b, b->used & ~BIG_BIN);
		b = b_next;
	}
	tmp = (char*)&g_malloc;
	while (tmp < &((char*)&g_malloc)[sizeof(t_malloc)])
		*(tmp++) = 0;
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
			if (b->next == NULL)
				return NULL;
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
			if (b->next == NULL)
				return NULL;
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
	if (b->next == NULL)
		return NULL;
	b = b->next;
	b->next = NULL;
	b->used = alloc_size;
	b->used |= BIG_BIN;
	DBG_PRINT("BIG stored size: %lu, requested size: %lu", alloc_size, size);
	return (&b->mem[0]);
}

void			*calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	char	*tmp;

	size *= nmemb;
	ptr = malloc(size);
	tmp = ptr;
	if (ptr)
		while (tmp < &ptr[size])
			*(tmp++) = 0;
	return (ptr);
}

void			*malloc(size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_malloc.lock);
	DBG_PRINT("malloc called: %lu", size);
	if (g_malloc.sml_elem_size == 0)
		init();
	if (size == 0) {
		pthread_mutex_unlock(&g_malloc.lock);
		return (NULL);
	}
	else if (size <= g_malloc.sml_elem_size)
		ret = (malloc_sml());
	else if (size <= g_malloc.med_elem_size)
		ret = (malloc_med());
	else
		ret = (malloc_big(size));
	DBG_PRINT("malloc returns %p", ret);
	pthread_mutex_unlock(&g_malloc.lock);
	return (ret);
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
