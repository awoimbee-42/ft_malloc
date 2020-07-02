/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_lots_cumulate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 23:05:30 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/03 00:41:01 by awoimbee         ###   ########.fr       */
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
		for (char* ss = ptr[i]; ss < &ptr[i][1024 * 1024 * 1024]; ss = &ss[512])
			memcpy(ss, str512, 512);
	}
	for (int i = 0; i < 8; ++i)
	{
		free(ptr[i]);
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
}
