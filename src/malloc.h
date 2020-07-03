/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:39:13 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/03 02:50:52 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <inttypes.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <sys/mman.h>

#include <stdio.h>

# define DEBUG	1

# define BIN_SIZE		100
# define SML_PAGE_NB	9
# define MED_PAGE_NB	409
# define ALIGNMENT		16

/*
**	Calculate preferred page numbers in python:
**	PAGE_SIZE = 1024 * 4
**	RESERVED_PER_BIN = 16 + 8
**	ALIGNMENT = 16
**	for n in range(1, 25000):
**		unused_per_page = int((n * PAGE_SIZE - RESERVED_PER_BIN) / 100) % ALIGNMENT
**		real_unused_per_page = ((n * PAGE_SIZE - RESERVED_PER_BIN) / 100) % ALIGNMENT
**		if (unused_per_page == 0):
**			print("page_nb:", n, "unused_per_page:", real_unused_per_page);
*/

# define SML_BIN (((__uint128_t) 0x20) << 120)
# define MED_BIN (((__uint128_t) 0x40) << 120)
# define BIG_BIN (((__uint128_t) 0x80) << 120)

typedef unsigned int	uint;
typedef __uint128_t		t_uint128;

# if DEBUG == 1
#  define DBG_PRINT(format, ...) fprintf(stderr,"-- DBG "format" --\n",__VA_ARGS__)
#  define ERR_PRINT(format, ...) fprintf(stderr, "-- ERR "format" --\n", __VA_ARGS__)
# else
#  define DBG_PRINT(format, ...) write(1, NULL, 0)
#  define ERR_PRINT(format, ...) fprintf(stderr, format, __VA_ARGS__)
# endif

# if BIN_SIZE > 128
#  error "Maximum bin size is 126"
# endif
# if (SML_PAGE_NB * 4096 - ALIGNMENT) / 100 % 16 != 0
#  warning "Most systems have 4kib pages, it is recommended that (SML_PAGE_NB * 4096 - 16) / 100 % 16 == 0"
# endif
# if (MED_PAGE_NB * 4096 - ALIGNMENT) / 100 % 16 != 0
#  warning "Most systems have 4kib pages, it is recommended that (MED_PAGE_NB * 4096 - 16) / 100 % 16 == 0"
# endif

typedef struct	s_malloc
{
	struct s_bin	*bins;
	pthread_mutex_t	lock;
	uint32_t		sml_map_size;
	uint16_t		sml_elem_size;
	uint32_t		med_map_size;
	uint16_t		med_elem_size;
}				t_malloc;

typedef struct	s_bin
{
	struct s_bin	*next;
	t_uint128		used;
	char			mem[];
}				t_bin;

extern t_malloc	g_malloc;

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);

#endif
