/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:39:13 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/03 00:38:05 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "params.h"
# include <string.h>
# include <sys/mman.h>
# include <unistd.h>
# include <inttypes.h>
# include <pthread.h>
# include <stdbool.h>

# define SML_BIN ((__uint128_t) 0x20) << 120
# define MED_BIN ((__uint128_t) 0x40) << 120
# define BIG_BIN ((__uint128_t) 0x80) << 120
# define ANY_BIN (SML_BIN | MED_BIN | BIG_BIN)

typedef unsigned int uint;
typedef __uint128_t bitfield_t;
typedef __uint128_t t_uint128;

#include <stdio.h>
# if DEBUG == 1
#  define DBG_PRINT(format, ...) fprintf(stderr,"\e[1;34m"format"\e[0m",__VA_ARGS__)
#  define ERR_PRINT(format, ...) fprintf(stderr, "\e[1;31m"format"\e[0m", __VA_ARGS__)
# else
#  define DBG_PRINT(format, ...)
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
	struct s_bin*	next;
	struct s_bin*	_unused;
	t_uint128		used;
	char			mem[];
}				t_bin;

// typedef enum	e_bin_size
// {
// 	SML = SML_BIN,
// 	MED = MED_BIN,
// 	BIG = BIG_BIN
// }				t_bin_size;

// extern t_bin *g_bins;
// extern t_inf g_inf;
extern t_malloc g_malloc;

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);
// const char		*bin_size_name(t_bin_size b);

#endif
