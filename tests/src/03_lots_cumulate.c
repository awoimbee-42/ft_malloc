/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_lots_cumulate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 23:05:30 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/03 17:05:15 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void malloc_lots_cumulate_small_basic()
{
	char*		ptr[1000];

	for (int i = 0; i < 1000; ++i)
	{
		assert((ptr[i] = malloc(128)));
	}
	for (int i = 0; i < 1000; ++i)
	{
		free(ptr[i]);
	}
}


void malloc_lots_cumulate_small()
{
	char*		ptr[1000];

	for (int i = 0; i < 1000; ++i)
	{
		assert((ptr[i] = malloc(128)));
		memcpy(ptr[i], str128, 128);
	}
	for (int i = 0; i < 1000; ++i)
	{
		assert(memcmp(ptr[i], str128, 128) == 0);
		free(ptr[i]);
	}
}


void malloc_lots_cumulate_med()
{
	char*		ptr[1000];

	for (int i = 0; i < 1000; ++i)
	{
		assert((ptr[i] = malloc(512)));
		memcpy(ptr[i], str512, 512);
	}
	for (int i = 0; i < 1000; ++i)
	{
		assert(memcmp(ptr[i], str512, 512) == 0);
		free(ptr[i]);
	}
}


void malloc_lots_cumulate_big()
{
	char*		ptr[8];

	for (int i = 0; i < 8; ++i)
	{
		assert((ptr[i] = malloc(1024 * 1024 * 1024)));
		for (
			char* ss = ptr[i];
			ss < &ptr[i][1024 * 1024 * 1024];
			ss = &ss[512]
		) {
			memcpy(ss, str512, 512);
		}
	}
	for (int i = 0; i < 8; ++i)
	{
		free(ptr[i]);
	}
}

void malloc_lots_cumulate_mixed(void)
{
	#define TRIES		5
	#define NB			800
	#define INT_THIRD	(__INT32_MAX__ / 3)

	char*			ptr[NB];
	size_t			alloc_size[NB];

	for (int seed = 0; seed < TRIES; seed++) {
		srandom(time(NULL));
		for (int i = 0; i < NB; i++) {
			alloc_size[i] = random();
			int mask = random();
			if (mask > INT_THIRD * 2)
				alloc_size[i] = i;
			else if (mask < INT_THIRD)
				alloc_size[i] = 2000 - i;
			alloc_size[i] %= 2000000LU;
			ptr[i] = malloc(alloc_size[i]);
			if (ptr[i])
				memset(ptr[i], 99, alloc_size[i]);
		}
		for (int i = 0; i < NB; i++) {
			if (ptr[i])
				for (size_t k=0; k<alloc_size[i]; k++) {assert(ptr[i][k] == 99);}
			free(ptr[i]);
		}
	}
}

void test_03_lots_cumulate(void)
{
	write(1, "malloc_lots_cumulate_small_basic...\n", 36);
	malloc_lots_cumulate_small_basic();
	write(1, "malloc_lots_cumulate_small...\n", 30);
	malloc_lots_cumulate_small();
	write(1, "malloc_lots_cumulate_med...\n", 28);
	malloc_lots_cumulate_med();
	write(1, "malloc_lots_cumulate_big...\n", 28);
	malloc_lots_cumulate_big();
	write(1, "malloc_lots_cumulate_mixed...\n", 30);
	malloc_lots_cumulate_mixed();
}
