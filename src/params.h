/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:36:03 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/21 17:03:09 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_PARAMS_H
# define MALLOC_PARAMS_H

# define malloc		malloc_orig
# define free		free_orig
# define realloc	realloc_orig
# undef malloc
# undef free
# undef realloc

# define BIN_SIZE 100
# define SMALL_PAGE_NB	1
# define MED_PAGE_NB	2

# if BIN_SIZE > 128
#  error "BIN_SIZE shall be equal or smaller to the numberof bits in uint128_t (bfield_t)"
# endif

typedef unsigned int uint;
typedef __uint128_t bitfield_t;

#endif
