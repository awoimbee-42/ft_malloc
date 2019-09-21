/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:39:13 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/21 21:54:23 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "params.h"
# include <string.h>
# include <sys/mman.h>
# include <unistd.h>
# include <inttypes.h>

typedef struct	s_bin_info
{
	size_t			map_size;
	size_t			elem_size;
}				t_bin_info;

typedef struct	s_inf
{
	t_bin_info		small;
	t_bin_info		med;
}				t_inf;

typedef struct	s_bin
{
	__uint128_t		used; // only BIN_SIZE bits are really used
	char			mem[];
}				t_bin;

typedef struct	s_big_bin
{
	void			*mem;
	size_t			size;
	char			mem_after_state[512];
}				t_big_bin;

typedef struct	s_bins
{
	t_bin			*s[20];
	t_bin			*m[20];
	t_big_bin		*b[20];
}				t_bins;

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);

#endif
