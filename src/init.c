/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:03:13 by awoimbee          #+#    #+#             */
/*   Updated: 2020/09/09 15:37:14 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intrin_malloc.h"

void			init(void)
{
	size_t		page_size;

	if (g_bin.sml_elem_size != 0)
		return ;
	page_size = getpagesize();
	g_bin.sml_map_size = page_size * SML_PAGE_NB;
	g_bin.sml_elem_size = (page_size * SML_PAGE_NB - sizeof(t_bin))
		/ BIN_SIZE;
	g_bin.sml_elem_size -= g_bin.sml_elem_size % ALIGNMENT;
	g_bin.med_map_size = page_size * MED_PAGE_NB;
	g_bin.med_elem_size = (page_size * MED_PAGE_NB - sizeof(t_bin))
		/ BIN_SIZE;
	g_bin.med_elem_size -= g_bin.sml_elem_size % ALIGNMENT;
	DBG_PRINT(
		"\n"
		"\tsml_elem_size: %1$9lu (%1$#9lx)\n"
		"\tmed_elem_size: %2$9lu (%2$#9lx)\n",
		g_bin.sml_elem_size,
		g_bin.med_elem_size);
}

void __attribute__((visibility("default")))			free_all(void)
{
	t_bin		*b;
	t_bin		*b_next;
	char		*tmp;

	b = g_bin.bins;
	while (b)
	{
		b_next = b->next;
		if (b->used & sml_bin())
			munmap(b, g_bin.sml_map_size);
		else if (b->used & med_bin())
			munmap(b, g_bin.med_map_size);
		else
			munmap(b, b->used & ~big_bin());
		b = b_next;
	}
	tmp = (char*)&g_bin;
	while (tmp < ((char*)&g_bin) + sizeof(t_malloc))
		*(tmp++) = 0;
}
