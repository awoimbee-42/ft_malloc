/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:43:51 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/23 23:24:09 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "op_bit.h"
#include <stdio.h>

t_bin*	g_bins;
t_inf	g_inf;

void			*mmap_malloc(size_t size)
{
	void* ptr;

	ptr = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		write(1, "FUCK\n", 5); // TODO
	return (ptr);
}

void			init_info(void)
{
	const size_t page_size = getpagesize();
	size_t page_nb[2] = {SML_MIN_PAGE_NB, MED_MIN_PAGE_NB};

	for (int i = 0; i < 2; ++i)
	{
		while ((page_nb[i] * page_size - sizeof(t_bin)) / BIN_SIZE % ALIGNMENT != 0)
		++page_nb[i];
		g_inf.arr[i].map_size = page_size * page_nb[i];
		g_inf.arr[i].elem_size = (g_inf.arr[i].map_size - sizeof(t_bin)) / BIN_SIZE;
	}
	DBG_PRINT(
		"Init done:\n"
			"\tpage_size: %lu\n"
			"\tsmall:\n"
				"\t\tnb_pages: %lu\n"
				"\t\telem_size: %lu\n"
			"\tmed:\n"
				"\t\tnb_page: %lu\n"
				"\t\telem_size: %lu\n",
		page_size,
		page_nb[0], g_inf.small.elem_size,
		page_nb[1], g_inf.med.elem_size);
}

void			*malloc_(t_bin_size size)
{
	/* if no bin has been created */
	if (!g_bins)
	{
		g_bins = mmap_malloc(g_inf.arr[size].map_size);

		bitfield_set_bin_size(&g_bins->used, size);
		DBG_PRINT("stored size: %d, requested size: %d\n", bitfield_get_bin_size(g_bins->used), size);
		bitfield_set_bit(&g_bins->used, 0);
		return (&g_bins->mem[0]);
	}

	t_bin*	b = g_bins;
	while (1)
	{
		if (bitfield_get_bin_size(b->used) == size)
		{
			uint empty_spot = bitfield_first_zero(b->used);
			if (empty_spot != BIN_SIZE)
			{
				DBG_PRINT("malloc: found empty spot at %u in bin type %u\n", empty_spot, size);
				bitfield_set_bit(&b->used, empty_spot);
				return (&b->mem[empty_spot * g_inf.arr[size].elem_size]);
			}
		}
		if (b->next_bin == NULL)
		{

			DBG_PRINT("malloc: creating new bin\n", NULL);
			b->next_bin = mmap_malloc(g_inf.arr[size].map_size);
			bitfield_set_bin_size(&b->next_bin->used, size);
			bitfield_set_bit(&b->next_bin->used, 0);
			return (&b->next_bin->mem[0]);
		}
		b = b->next_bin;
	}
}

void			*malloc_big(size_t size)
{
	return (NULL);
}

void			*malloc(size_t size)
{
	if (g_inf.small.elem_size == 0)
		init_info();
	if (size <= g_inf.small.elem_size)
		return (malloc_(SML));
	else if (size <= g_inf.med.elem_size)
		return (malloc_(MED));
	else
		return (malloc_big(size));
}

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

void			free(void *ptr)
{
	if(ptr == NULL)
		{DBG_PRINT("Free: NULL pointer\n", NULL); return;}
	for (t_bin *b = g_bins; b != NULL; b = b->next_bin)
	{
		const uintptr_t		uptr = (uintptr_t)ptr;
		const uintptr_t		ubin = (uintptr_t)b;
		const t_bin_info	bininf = g_inf.arr[bitfield_get_bin_size(b->used)];
		if ((ubin + bininf.map_size) - ubin != bininf.map_size)
			ERR_PRINT("DOOM\n", NULL);
		if (uptr > ubin && uptr < (ubin + bininf.map_size))
		{
			uint index = (uptr - (uintptr_t)&b->mem[0]) / bininf.elem_size;
			bitfield_unset_bit(&b->used, index);
			DBG_PRINT("Free: unset in %u bin, index %u\n",
				bitfield_get_bin_size(b->used),
				index);
			return ;
		}
	}
	ERR_PRINT("free: unknown pointer %p\n", ptr);
	return ;
}

void	print_allocs(void)
{
	for (t_bin *b = g_bins; b != NULL; b = b->next_bin)
	{
		const char* types[3] = {
			"SMALL",
			"MEDIUM",
			"BIG"
		};

		fprintf(stderr, "BIN: %s: first hole %d\n",
			types[bitfield_get_bin_size(b->used)],
			bitfield_first_zero(b->used));
	}
}
