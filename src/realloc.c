/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:34:51 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/03 17:28:39 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static inline void	*yo_man_realloc(void *p, size_t new_siz, size_t old_siz) {
	void	*new_ptr;

	pthread_mutex_unlock(&g_malloc.lock);
	new_ptr = malloc(new_siz);
	if (!new_ptr) {
		ERR_PRINT("MALLOC FAILED", NULL);
		return NULL;
	}
	memcpy(new_ptr, p, old_siz);
	free(p);
	return (new_ptr);
}

void			*reallocarray(void *ptr, size_t nmemb, size_t size)
{
	return (realloc(ptr, nmemb * size));
}

void			*realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc(size));
	pthread_mutex_lock(&g_malloc.lock);
	for (t_bin *b = g_malloc.bins; b != NULL; b = b->next)
	{
		if (b->used & BIG_BIN) {
			if (b->mem != ptr)
				continue;
			size_t alloc_size = (b->used & ~BIG_BIN) - sizeof(t_bin);
			DBG_PRINT("alloc_size: %d\n", (int)alloc_size);
			if (alloc_size >= size)
			{
				write(1, "pute\n", 5);
				pthread_mutex_unlock(&g_malloc.lock);return (ptr);}

			return (yo_man_realloc(ptr, size, alloc_size));
		}
		else if (b->used & MED_BIN) {
			if (!((void*)b < ptr && ptr < (void*)(b + g_malloc.med_map_size)))
				continue;
			if (size <= (size_t)g_malloc.med_elem_size)
				{pthread_mutex_unlock(&g_malloc.lock);return (ptr);}
			return (yo_man_realloc(ptr, size, g_malloc.med_elem_size));
		}
		else if (b->used & SML_BIN) {
			if (!((void*)b < ptr && ptr < (void*)(b + g_malloc.sml_map_size)))
				continue;
			if (size <= (size_t)g_malloc.sml_elem_size)
				{pthread_mutex_unlock(&g_malloc.lock);return (ptr);}
			return (yo_man_realloc(ptr, size, g_malloc.sml_elem_size));
		}
	}
	ERR_PRINT("Realloc: unknown pointer (%p, %lu)", ptr, size);
	pthread_mutex_unlock(&g_malloc.lock);
	return (NULL);
}
