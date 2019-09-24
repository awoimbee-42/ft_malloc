/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:39:13 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/24 23:38:26 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "params.h"
# include <string.h>
# include <sys/mman.h>
# include <unistd.h>
# include <inttypes.h>

/* used to access array members, modifying will cause overflow */
# define SML_BIN 0b00
# define MED_BIN 0b01
# define BIG_BIN 0b10

typedef unsigned int uint;
typedef __uint128_t bitfield_t;

#include <stdio.h>
# if DEBUG == 1
#  define DBG_PRINT(format, ...) fprintf(stderr,"\e[1;34m"format"\e[0m",__VA_ARGS__)
#  define ERR_PRINT(format, ...) fprintf(stderr, "\e[1;31m"format"\e[0m", __VA_ARGS__)
# else
#  define DBG_PRINT(format, ...)
#  define ERR_PRINT(format, ...) fprintf(stderr, format, __VA_ARGS__)
# endif

# if BIN_SIZE > 126
#  error "Maximum bin size is 126"
# endif
# if (SML_MIN_PAGE_NB * 4096 - ALIGNMENT) / 100 % 16 != 0
#  warning "Most systems have 4kib pages, it is recommended that (SML_MIN_PAGE_NB * 4096 - 16) / 100 % 16 == 0"
# endif
# if (MED_MIN_PAGE_NB * 4096 - ALIGNMENT) / 100 % 16 != 0
#  warning "Most systems have 4kib pages, it is recommended that (MED_MIN_PAGE_NB * 4096 - 16) / 100 % 16 == 0"
# endif

typedef struct	s_bin_info
{
	size_t			map_size;
	size_t			elem_size;
}				t_bin_info;

typedef union	u_inf
{
	struct
	{
		t_bin_info	small;
		t_bin_info	med;
	};
	t_bin_info		arr[2];
}				t_inf;
// 100+2+65 = 167
typedef struct	s_bin
{
	__uint128_t		used;
	struct s_bin*	next_bin;
	uint64_t		spacer;
	char			mem[];
}				t_bin;

typedef enum	s_bin_size
{
	SML = SML_BIN,
	MED = MED_BIN,
	BIG = BIG_BIN
}				t_bin_size;

extern t_bin *g_bins;
extern t_inf g_inf;

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);

#endif
