/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:34:51 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/16 19:27:04 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intrin_malloc.h"

static inline void	*yo_man_realloc(void *p, size_t new_siz, size_t old_siz)
{
	void	*new_ptr;

	new_ptr = malloc_mut(new_siz);
	if (!new_ptr)
	{
		ERR_PRINT("MALLOC FAILED", NULL);
		return (NULL);
	}
	memcpy(new_ptr, p, new_siz > old_siz ? old_siz : new_siz);
	free_mut(p);
	return (new_ptr);
}

void				*reallocarray(void *ptr, size_t nmemb, size_t size)
{
	return (realloc(ptr, nmemb * size));
}

static size_t		get_mem_size(void *ptr, t_bin *b)
{
	if (b->used & big_bin())
	{
		if (b->mem == ptr)
			return ((b->used & ~big_bin()) - sizeof(t_bin));
	}
	else if (b->used & med_bin())
	{
		if ((void*)b->mem <= ptr && ptr < med_bin_end(b))
			return (g_bin.med_elem_size);
	}
	else if (b->used & sml_bin())
	{
		if ((void*)b->mem <= ptr && ptr < sml_bin_end(b))
			return (g_bin.sml_elem_size);
	}
	return (0);
}

static void			*inner_realloc(void *ptr, size_t size)
{
	t_bin	*b;
	size_t	mem_size;

	if (ptr == NULL)
		return (malloc_mut(size));
	DBG_PRINT("realloc %lu", size);
	b = (t_bin*)&g_bin;
	while ((b = b->next))
	{
		mem_size = get_mem_size(ptr, b);
		if (mem_size == 0)
			continue;
		if (size <= mem_size)
			return (ptr);
		DBG_PRINT("yo realloc mem_size: %lu requested: %lu", mem_size, size);
		return (yo_man_realloc(ptr, size, mem_size));
	}
	ERR_PRINT("Realloc: unknown pointer (%p, %lu)", ptr, size);
	return (NULL);
}

void				*realloc(void *ptr, size_t size)
{
	void	*ret;

	pthread_mutex_lock(&g_bin.lock);
	init();
	ret = inner_realloc(ptr, size);
	pthread_mutex_unlock(&g_bin.lock);
	return (ret);
}
