/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_lots_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 23:05:30 by awoimbee          #+#    #+#             */
/*   Updated: 2020/04/29 23:24:22 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void malloc_lots_basic_small()
{
	char*		s;

	for (int i = 0; i < 1000; ++i)
	{
		assert((s = malloc(128)));
		memcpy(s, str128, 128);
		assert(memcmp(s, str128, 128) == 0);
		free(s);
	}
}


void malloc_lots_basic_med()
{
	char*		s;

	for (int i = 0; i < 1000; ++i)
	{
		assert((s = malloc(512)));
		memcpy(s, str512, 512);
		assert(memcmp(s, str512, 512) == 0);
		free(s);
	}
}


void malloc_lots_basic_big()
{
	char*		s;

	for (int i = 0; i < 1000; ++i)
	{
		assert((s = malloc(1024 * 1024)));
		for (char* ss = s; ss < s + (1024*1024); ss += 512)
			memcpy(ss, str512, 512);
		free(s);
	}
}


void test_02_lots_basic(void)
{
	write(1, "malloc_lots_basic_small...\n", 27);
	malloc_lots_basic_small();
	write(1, "malloc_lots_basic_med...\n", 25);
	malloc_lots_basic_med();
	write(1, "malloc_lots_basic_big...\n", 25);
	malloc_lots_basic_big();
}
