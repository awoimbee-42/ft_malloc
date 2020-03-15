/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:43:51 by awoimbee          #+#    #+#             */
/*   Updated: 2019/10/11 20:51:39 by awoimbee         ###   ########.fr       */
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
				DBG_PRINT("malloc: found empty spot at %u in bin type %s\n", empty_spot, bin_size_name(size));
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
	const size_t page_size = getpagesize();
	const size_t alloc_size = (size + sizeof(t_bin)) + page_size - (size + sizeof(t_bin)) % page_size; // (size + sizeof(t_bin)) == page_size is unlikely
	t_bin* new_bin;

	new_bin = mmap_malloc(alloc_size);
	bitfield_set_bin_size(&new_bin->used, BIG);
	bitfield_set_big_alloc_size(&new_bin->used, alloc_size);
	DBG_PRINT("BIG stored size: %d, requested size: %d\n", alloc_size, size);

	if (!g_bins)
		g_bins = new_bin;
	else
	{
		t_bin *b;
		for (b = g_bins; b->next_bin != NULL; b = b->next_bin)
			;
		b->next_bin = new_bin;
	}
	return (&new_bin->mem[0]);
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

// int main(){
// 		char*		s;

// 	for (int i = 0; i < 1000; ++i)
// 	{
// 		if (!(s = malloc(1024 * 1024)))
// 		;	// ck_abort_msg("malloc(1024 * 1024) failed!");
// 		fprintf(stderr, "%p, %lu\n", s, (size_t)s % 16UL);
// 		for (int i = 0; i < 1024*1024; ++i)
// 			s[i] = 'a';
// 		write(1, s, 1024*1024);
// 		write(1, "\nlol\n", 5);
// 		memset(s, 200, 10);
// 		// for (char* ss = s; ss < s + (1024*1024); ss += 512)
// 			// memcpy(ss, str512, 512);
// 		// for (char* ss = s; ss < s + (1024*1024); ss += 512)
// 			// ck_assert(memcmp(ss, str512, 512) == 0);
// 		free(s);
// 	}
// }
