/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 17:25:47 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/16 17:27:23 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intrin_malloc.h"

void	*med_bin_end(t_bin *b)
{
	return ((void*)((char*)b + g_bin.med_map_size));
}

void	*sml_bin_end(t_bin *b)
{
	return ((void*)((char*)b + g_bin.sml_map_size));
}
