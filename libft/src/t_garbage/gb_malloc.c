/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 20:44:45 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/06 00:28:04 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/t_garbage.h>
#include <stdlib.h>

void		*gb_malloc(t_garbage *gb, size_t size)
{
	if (gb->arr_len == gb->mem_len - 1)
		intrin_gb_extend(gb);
	gb->pointers[gb->arr_len] = malloc(size);
	if (!__builtin_expect((long)gb->pointers[gb->arr_len], 1))
		intrin__gb_fail(gb);
	return (gb->pointers[gb->arr_len++]);
}
