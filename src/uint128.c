/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint128.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:17:54 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/16 18:24:57 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intrin_malloc.h"

/*
**	Again, fuck the norme
**	This is so bad it makes me want to cry
*/

t_uint128		get1(void)
{
	return (1);
}

t_uint128		sml_bin(void)
{
	return ((get1() * 0x20) << 120);
}

t_uint128		med_bin(void)
{
	return ((get1() * 0x40) << 120);
}

t_uint128		big_bin(void)
{
	return ((get1() * 0x80) << 120);
}

t_uint128		any_bin(void)
{
	return (sml_bin() | med_bin() | big_bin());
}
