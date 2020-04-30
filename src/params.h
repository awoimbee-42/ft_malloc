/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:36:03 by awoimbee          #+#    #+#             */
/*   Updated: 2020/04/29 23:24:44 by awoimbee         ###   ########.fr       */
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

# define DEBUG	1

# define BIN_SIZE	100 /* the bitfield is 128 long, 2 are reserved */
# define SML_MIN_PAGE_NB	9
# define MED_MIN_PAGE_NB	409
# define ALIGNMENT	16

/*
**	Calculate preferred page numbers in python:
	PAGE_SIZE = 1024 * 4
	RESERVED_PER_BIN = 16 + 8
	ALIGNMENT = 16
	for n in range(1, 25000):
		unused_per_page = int((n * PAGE_SIZE - RESERVED_PER_BIN) / 100) % ALIGNMENT
		real_unused_per_page = ((n * PAGE_SIZE - RESERVED_PER_BIN) / 100) % ALIGNMENT
		if (unused_per_page == 0):
			print("page_nb:", n, "unused_per_page:", real_unused_per_page);
*/

#endif
