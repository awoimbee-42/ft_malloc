/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:27:29 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/24 22:26:38 by awoimbee         ###   ########.fr       */
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

static inline void			bitfield_unset_bit(bitfield_t *bf, uint i)
{
	bitfield_t	mask;

	mask = ((bitfield_t)1) << i;
	*bf = *bf & ~mask;
}

static inline void			bitfield_set_bin_size(bitfield_t *bf, t_bin_size s)
{
	bitfield_t	mask = (bitfield_t)s << 126;
	*bf = *bf | mask;
}

static inline t_bin_size	bitfield_get_bin_size(bitfield_t bf)
{
	return (bf >> 126);
}

static inline size_t		bitfield_get_big_alloc_size(bitfield_t bf)
{
	return ((size_t)bf);
}

/* Do not use to resize an existing bin! */
static inline void			bitfield_set_big_alloc_size(bitfield_t *bf, size_t size)
{
	*bf = *bf | size;
}

#endif
