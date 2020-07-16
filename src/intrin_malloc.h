/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intrin_malloc.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:39:13 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/16 17:37:07 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTRIN_MALLOC_H
# define INTRIN_MALLOC_H

# include "malloc.h"

# include <inttypes.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <sys/mman.h>
# include <sys/types.h>

# include <stdio.h>

# define DEBUG	0

# define BIN_SIZE		100
# define SML_PAGE_NB	9
# define MED_PAGE_NB	409
# define ALIGNMENT		16

# define SML_BIN (((__uint128_t) 0x20) << 120)
# define MED_BIN (((__uint128_t) 0x40) << 120)
# define BIG_BIN (((__uint128_t) 0x80) << 120)

typedef __uint128_t		t_uint128;

# if DEBUG == 1
#  define DBG_PRINT(format, ...) \
	do { \
		fprintf(stderr,"-- DBG "format" --\n",__VA_ARGS__); \
		fflush(stderr); \
	} while (0)
#  define ERR_PRINT(format, ...) \
	do { \
		fprintf(stderr, "-- ERR "format" --\n", __VA_ARGS__); \
		fflush(stderr); \
	} while (0)
# else
#  define DBG_PRINT(format, ...) write(1, NULL, 0)
#  define ERR_PRINT(format, ...) \
	do { \
		fprintf(stderr, "ERROR "format"\n", __VA_ARGS__); \
		fflush(stderr); \
	} while (0)
# endif

# if BIN_SIZE > 128
#  error "Maximum bin size is 126"
# endif
# if (SML_PAGE_NB * 4096 - ALIGNMENT) / 100 % 16 != 0
#  warning "Most systems have 4kib pages: (SML_PAGE_NB*4096 - 16)/100 % 16 = 0"
# endif
# if (MED_PAGE_NB * 4096 - ALIGNMENT) / 100 % 16 != 0
#  warning "Most systems have 4kib pages: (MED_PAGE_NB*4096 - 16)/100 % 16 = 0"
# endif

typedef struct	s_malloc
{
	struct s_bin	*bins;
	pthread_mutex_t	lock;
	size_t			sml_map_size;
	size_t			sml_elem_size;
	size_t			med_map_size;
	size_t			med_elem_size;
}				t_malloc;

typedef struct	s_bin
{
	struct s_bin	*next;
	t_uint128		used;
	char			mem[];
}				t_bin;

typedef bool(*t_free_fn)(void*, struct s_bin**);

extern t_malloc	g_bin;

void			init(void);
void			free_mut(void *ptr);
void			*malloc_mut(size_t size);

void			free_all(void);
void			free(void *ptr);
void			*malloc(size_t size);
void			*calloc(size_t nmemb, size_t size);
void			*reallocarray(void *ptr, size_t nmemb, size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);

void			*med_bin_end(t_bin *b);
void			*sml_bin_end(t_bin *b);

#endif
