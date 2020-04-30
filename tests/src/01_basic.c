/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 00:12:46 by awoimbee          #+#    #+#             */
/*   Updated: 2020/04/29 23:19:25 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void malloc_basic_small()
{
	const char*	cs = "Hello World!";
	char*		s;

	assert((s = malloc(13)));
	memcpy(s, cs, 13);
	assert(strcmp(s, cs) == 0);
	free(s);
}

void malloc_basic_med()
{
	char		cs[512];
	char*		s;

	srand(time(NULL));
	for (int i = 0; i < 512; ++i)
		cs[i] = rand();
	assert((s = malloc(512)));
	memcpy(s, cs, 512);
	assert(memcmp(s, cs, 512) == 0);
	free(s);
}


void malloc_basic_big()
{
	unsigned char*	s;

	assert((s = malloc(1024*1024)));
	memset(s, 255, 1024*1024);
	free(s);
}


void test_01_basic(void)
{
	write(1, "malloc_basic_small...\n", 22);
	malloc_basic_small();
	write(1, "malloc_basic_med...\n", 20);
	malloc_basic_med();
	write(1, "malloc_basic_big...\n", 20);
	malloc_basic_big();
}
