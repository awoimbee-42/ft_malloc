/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:39:13 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/15 19:36:25 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define malloc		malloc_orig
# define free		free_orig
# define realloc	realloc_orig
# undef malloc
# undef free
# undef realloc

// # define SIZ_BIG	(1024 * 1024)

#include <string.h>
#include <sys/mman.h>

typedef struct	s_inf
{
	size_t			small_map_size;
	size_t			small_mem_size;
	size_t			small_state_size;
	size_t			small_elem_size;

	size_t			med_map_size;
	size_t			med_elem_size;
	size_t			med_mem_size;
	size_t			med_state_size;
}				t_inf;

typedef struct	s_sbin
{
	__uint128_t		used; //only 100 bits are really used
	char			mem[];
}				t_sbin;

typedef struct	s_mbin
{
	void			*mem;
	char			mem_state[SIZ_MED / 8 + 1];
}				t_mbin;

typedef struct	s_bbin
{
	void			*mem;
	size_t			size;
	char			mem_after_state[512];
}				t_bbin;

typedef struct	s_bins
{
	t_sbin			*s[20];
	t_mbin			*m[20];
	t_bbin			*b[20];
}				t_bins;

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);

#endif
