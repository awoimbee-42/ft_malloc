/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_allocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:33:26 by awoimbee          #+#    #+#             */
/*   Updated: 2020/09/09 17:46:18 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intrin_malloc.h"
#include <libft/ft_prtf.h>
#include <libft/ft_fd.h>

static void		sort_bins(void)
{
	t_bin	*b0;
	t_bin	*b1;
	t_bin	*tmp;

	b0 = (t_bin*)&g_bin;
	while (b0->next && b0->next->next)
	{
		b1 = b0;
		b0 = b0->next;
		if (b0->mem > b0->next->mem)
		{
			b1->next = b0->next;
			tmp = b1->next->next;
			b1->next->next = b0;
			b0->next = tmp;
			b0 = (t_bin*)&g_bin;
		}
	}
}

static size_t	print_bin(t_bin *b, size_t elem_size, const char *b_name)
{
	int			i;
	size_t		used;

	ft_putstr(b_name);
	used = 0;
	i = -1;
	while (++i < BIN_SIZE)
	{
		if (!((b->used & ~any_bin()) & (get1() << i)))
			continue;
		used += elem_size;
		ft_printf(
			"      \t %p - %p: %lu bytes\n",
			(size_t)(b->mem + (elem_size * i)),
			(size_t)(b->mem + (elem_size * (i + 1))),
			elem_size);
	}
	return (used);
}

static void		print_big_bin(t_bin *b, size_t *tot_used, size_t *tot_alloc)
{
	size_t		size;

	size = b->used & ~big_bin();
	*tot_alloc += size;
	*tot_used += size - sizeof(t_bin);
	ft_printf(
		"BIG   \t %p - %p: %lu bytes\n",
		b->mem,
		(size_t)b->mem + size,
		size);
}

void __attribute__((visibility("default")))			show_alloc_mem(void)
{
	t_bin		*b;
	size_t		allocated;
	size_t		used;

	allocated = 0;
	used = 0;
	sort_bins();
	b = (t_bin*)&g_bin;
	while (b->next)
	{
		b = b->next;
		if (b->used & big_bin())
			print_big_bin(b, &used, &allocated);
		else if (b->used & med_bin())
		{
			allocated += g_bin.med_map_size;
			print_bin(b, g_bin.med_elem_size, "MEDIUM\n");
		}
		else if (b->used & sml_bin())
		{
			allocated += g_bin.sml_map_size;
			print_bin(b, g_bin.sml_elem_size, "SMALL \n");
		}
	}
	ft_printf("mmap mem: %lu bytes\nmalloc mem: %lu bytes\n", allocated, used);
}
