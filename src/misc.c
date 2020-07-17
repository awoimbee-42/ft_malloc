/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:25:47 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/16 19:39:52 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intrin_malloc.h"

void		*med_bin_end(const t_bin *b)
{
	return ((void*)((char*)b + g_bin.med_map_size));
}

void		*sml_bin_end(const t_bin *b)
{
	return ((void*)((char*)b + g_bin.sml_map_size));
}

void		*mmap_malloc(size_t size)
{
	void	*ptr;

	ptr = mmap(
		NULL, size, PROT_WRITE | PROT_READ,
		MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}

uint		bin_empty_spot(const t_uint128 bfield)
{
	uint		spot;

	spot = 0;
	while (((bfield >> spot) & 1) == 1 && spot < 101)
		spot++;
	return (spot);
}
