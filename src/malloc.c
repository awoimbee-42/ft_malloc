/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:43:51 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/22 01:12:28 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "op_bit.h"
// #include <libft.h>
#include <stdio.h>

t_bins	g_bins;
t_inf	g_inf;
// 3 array de bins
// each array initialized at 20 bins
// each bin has data & freedata vec

// rbtree of free chunks

void			*mmap_malloc(size_t size)
{
	void* ptr;

	ptr = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		write(1, "FUCK\n", 5); // TODO
	return (ptr);
}

void			init_inf(void)
{
	size_t page_size = getpagesize();

	g_inf.small.map_size = page_size * SMALL_PAGE_NB;
	g_inf.small.elem_size = (g_inf.small.map_size - sizeof(__uint128_t)) / BIN_SIZE;

	g_inf.med.map_size = page_size * MED_PAGE_NB;
	g_inf.med.elem_size = (g_inf.med.map_size - sizeof(__uint128_t)) / BIN_SIZE;

	fprintf(
		stderr,
		"Init done:\n\tsmall:\n\t\tpage_size: %lu\n\t\telem_size: %lu\n\tmed:\n\t\tpage_size: %lu\n\t\telem_size: %lu\n",
		g_inf.small.map_size, g_inf.small.elem_size,
		g_inf.med.map_size, g_inf.med.elem_size);
}

void			*malloc_small(size_t size)
{
	for (int bin = 0; bin < 20; ++bin)
	{
		if (!g_bins.s[bin])
		{
			g_bins.s[bin] = mmap_malloc(g_inf.small.map_size);
			bitfield_set_bit(&g_bins.s[bin]->used, 0);
			return (g_bins.s[bin]->mem);
		}
		else
		{
			uint empty_spot = bitfield_first_zero(g_bins.s[bin]->used);
			if (empty_spot != BIN_SIZE)
			{
				bitfield_set_bit(&g_bins.s[bin]->used, empty_spot);
				return (&g_bins.s[bin]->mem[empty_spot * g_inf.small.elem_size]);
			}
		}
	}
	// TODO: ERROR THE FUCK OUT
}

void			*malloc_med(size_t size)
{
	for (int bin = 0; bin < 20; ++bin)
	{
		if (!g_bins.m[bin])
		{
			g_bins.m[bin] = mmap_malloc(g_inf.med.map_size);
			bitfield_set_bit(&g_bins.m[bin]->used, 0);
			return (g_bins.m[bin]->mem);
		}
		else
		{
			uint empty_spot = bitfield_first_zero(g_bins.m[bin]->used);
			if (empty_spot != BIN_SIZE)
			{
				bitfield_set_bit(&g_bins.m[bin]->used, empty_spot);
				return (&g_bins.m[bin]->mem[empty_spot * g_inf.med.elem_size]);
			}
		}
	}
	// TODO: ERROR THE FUCK OUT
}

void			*malloc_big(size_t size)
{
	return (NULL);
}

void			*malloc(size_t size)
{
	if (g_inf.small.elem_size == 0)
		init_inf();
	if (size <= g_inf.small.elem_size)
		return (malloc_small(size));
	else if (size <= g_inf.med.elem_size)
		return (malloc_med(size));
	else
		return (malloc_big(size));
}

void			*realloc(void *ptr, size_t size)
{
	return (NULL);
}

void			free(void *ptr)
{
	for (t_bin **b = g_bins.s; b != &g_bins.s[20]; ++b)
	{
		if ((uintptr_t)ptr > (uintptr_t)*b && (uintptr_t)ptr < ((uintptr_t)*b + (uintptr_t)g_inf.small.map_size))
		{
			uint index = ((uintptr_t)ptr - (uintptr_t)(*b)->mem[0]) / g_inf.small.elem_size;
			bitfield_unset_bit(&(*b)->used, index);
		}
	}
	for (t_bin **b = g_bins.m; b != &g_bins.m[20]; ++b)
	{
		if ((uintptr_t)ptr > (uintptr_t)*b && (uintptr_t)ptr < ((uintptr_t)*b + (uintptr_t)g_inf.med.map_size))
		{
			uint index = ((uintptr_t)ptr - (uintptr_t)&(*b)->mem[0]) / g_inf.med.elem_size;
			bitfield_unset_bit(&(*b)->used, index);
		}
	}
}

int main(){
	char*s=malloc(128);
	if (s==NULL)
		write(1, "PUTE\n", 5);
	strcpy(s, "hello i am fucked in the pute yoi je sai spas quoi ecrir euh c\n");
	write(1, s, 64);
	free(s);
	return (0);
}
