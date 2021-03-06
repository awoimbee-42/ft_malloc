/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:04:20 by awoimbee          #+#    #+#             */
/*   Updated: 2020/09/09 15:13:40 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intrin_malloc.h"

void __attribute__((visibility("default")))
	*calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	char	*tmp;

	size *= nmemb;
	ptr = malloc(size);
	tmp = ptr;
	if (ptr)
		while (tmp < &ptr[size])
			*(tmp++) = 0;
	return (ptr);
}
