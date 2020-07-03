/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:34:51 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/04 01:14:50 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static inline void	*yo_man_realloc(void *p, size_t new_siz, size_t old_siz) {
	void	*new_ptr;

	new_ptr = malloc_mut(new_siz);
	if (!new_ptr) {
		ERR_PRINT("MALLOC FAILED", NULL);
		return NULL;
	}
	memcpy(new_ptr, p, new_siz > old_siz ? old_siz : new_siz);
	free_mut(p);
	return (new_ptr);
}

void			*reallocarray(void *ptr, size_t nmemb, size_t size)
{
	return (realloc(ptr, nmemb * size));
}

void			*inner_realloc(void *ptr, size_t size)
{
	t_bin	*b[2];

	if (ptr == NULL)
		return (malloc_mut(size));
	DBG_PRINT("realloc %lu", size);
	b[1] = (t_bin*)&g_malloc;
	b[0] = b[1];
	while ((b[0] = b[0]->next))
	{
		if (b[0]->used & BIG_BIN) {
			if (b[0]->mem != ptr)
				continue;

			size_t mem_size = (b[0]->used & ~BIG_BIN) - sizeof(t_bin);
			if (size <= mem_size)
				return (ptr);
			DBG_PRINT("yo realloc BIG mem_size: %lu requested size: %lu", mem_size, size);

			return (yo_man_realloc(ptr, size, mem_size));
		}
		else if (b[0]->used & MED_BIN) {
			if (!((void*)b[0] < ptr && ptr < (void*)((char*)b[0] + g_malloc.med_map_size)))
				continue;
			if (size <= (size_t)g_malloc.med_elem_size)
				return (ptr);
			DBG_PRINT("yo realloc MED mem_size: %lu requested size: %lu", g_malloc.med_elem_size, size);
			return (yo_man_realloc(ptr, size, g_malloc.med_elem_size));
		}
		else if (b[0]->used & SML_BIN) {
			if (!((void*)b[0] < ptr && ptr < (void*)((char*)b[0] + g_malloc.sml_map_size)))
				continue;
			if (size <= (size_t)g_malloc.sml_elem_size)
				return (ptr);
			DBG_PRINT("yo realloc SML mem_size: %lu requested size: %lu", g_malloc.sml_elem_size, size);

			return (yo_man_realloc(ptr, size, g_malloc.sml_elem_size));
		}
		b[1] = b[0];
	}
	ERR_PRINT("Realloc: unknown pointer (%p, %lu)", ptr, size);
	return (NULL);
}


void			*realloc(void *ptr, size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_malloc.lock);
	init();
	ret = inner_realloc(ptr, size);
	pthread_mutex_unlock(&g_malloc.lock);
	return (ret);
}
