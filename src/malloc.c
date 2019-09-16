/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:43:51 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/16 15:35:31 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
// #include <libft.h>

t_bins	g_bins;
t_inf	g_inf;
// 3 array de bins
// each array initialized at 20 bins
// each bin has data & freedata vec

// rbtree of free chunks

int				check_free_bytes(char *mem_state, size_t check_size)
{
	for (; check_size != (size_t)-1; --check_size)
	{
		if ((mem_state[check_size / 8] & (1 << (check_size % 8))) != 0)
			return (0);
	}
	return (1);
}

void			init_inf(void)
{
	size_t page_size = getpagesize();
	g_inf.small_map_size = page_size;
	g_inf.small_mem_size = g_inf.small_map_size - sizeof(__uint128_t);

	// g_inf.med_map_size = 10 * page_size;
	// g_inf.med_mem_size = g_inf.small_map_size / 2 + g_inf.small_map_size / 4;
	// g_inf.med_state_size = g_inf.small_map_size / 4;
	// g_inf.med_elem_size = g_inf.small_mem_size / 100;
}

// mark a spot as used in a bin
void			mark_as_used(__uint128_t *used, int where)
{
	*used |= 1 << (where);
}

// finds an empty slot in a bin
int				find_empty(__uint128_t *used)
{
	for (int i = 0; i < 100; ++i)
	{
		if ((*used & (1 << i)) == 0)
			return (i);
	}
	return (-1);
}

void			*malloc_small(size_t size)
{
	for (int bin = 0; bin < 20; ++bin)
	{
		if (!g_bins.s[bin])
		{
			g_bins.s[bin] = mmap(
				NULL,
				g_inf.small_map_size,
				PROT_WRITE | PROT_READ,
				MAP_PRIVATE, -1, 0);
			mark_as_used(&g_bins.s[bin]->used, 0);
			return (g_bins.s[bin]->mem);
		}
		int available_space = find_empty(&g_bins.s[bin]->used);
		if (available_space != -1)
		{
			mark_as_used(&g_bins.s[bin]->used, available_space);
		}

		for (int off = 0; off < SIZ_SMAL - size - 1; ++off) // offset in bits
		{
			char *byte = &(g_bins.s[bin].mem_state[off / 8]);
			int bit = *byte & (1 << (off % 8));

			if (bit == 0)
			{
				if (check_free_bytes(byte, size))
			}
		}
	}
}

void			*malloc(size_t size)
{
	if (g_inf.small_elem_size == 0)
		init_inf();
	if (size <= g_inf.small_elem_size)
		return (malloc_small(size));
	else if (size <= g_inf.small_elem_size)
		return (malloc_med(size));
	else
		return (malloc_big(size));


	// static void *mapped = NULL;
	// void	*ptr;

	// if (mapped == NULL)
	// 	mapped = mmap(0, 1024*1024*1024, PROT_NONE, MAP_PRIVATE, -1, 0);
	// // ptr = mmap(somezhere in mapped, some size, PROT_READ|PROT_WRITE, MAP_PRIVATE, -1, 0);
	// ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
	// return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	return (NULL);
}

void			free(void *ptr)
{

}
