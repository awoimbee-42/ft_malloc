/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:27:29 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/21 21:31:48 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_BIT_H
# define OP_BIT_H

# include "params.h"

static inline uint 			bitfield_get_bit(bitfield_t bf, uint i)
{
	return (
		(bf >> i) & 1
	);
}

static inline uint			bitfield_first_zero(bitfield_t bf)
{
	uint	i = 0;

	while (bitfield_get_bit(bf, i) != 0)
		++i;
	return (i);
}

static inline void			bitfield_set_bit(bitfield_t *bf, uint i)
{
	bitfield_t	mask;

	mask = ((bitfield_t)1) << i;
	*bf = *bf | mask;
}

static inline void		bitfield_unset_bit(bitfield_t *bf, uint i)
{
	bitfield_t	mask;

	mask = 1 << (i - 1);
	*bf = *bf & ~mask;
}

#endif
