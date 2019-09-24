/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 00:12:46 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/24 22:51:05 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

START_TEST (malloc_basic_small)
{
	const char*	cs = "Hello World!";
	char*		s;

	if (!(s = my_malloc(13)))
		ck_abort_msg("malloc(13) failed!");
	memcpy(s, cs, 13);
	ck_assert(strcmp(s, cs) == 0);
	my_free(s);
}
END_TEST

START_TEST (malloc_basic_med)
{
	char		cs[512];
	char*		s;

	srand(time(NULL));
	for (int i = 0; i < 512; ++i)
		cs[i] = rand();
	if (!(s = my_malloc(512)))
		ck_abort_msg("malloc(512) failed!");
	memcpy(s, cs, 512);
	ck_assert(memcmp(s, cs, 512) == 0);
	my_free(s);
}
END_TEST

START_TEST (malloc_basic_big)
{
	unsigned char*	s;

	if (!(s = my_malloc(1024*1024)))
		ck_abort_msg("malloc(1024*1024) failed!");
	memset(s, 255, 1024*1024);
	my_free(s);
}
END_TEST

Suite	*build_suite_01_basic(void)
{
	Suite	*s = suite_create("01_basic");
	TCase	*tc = tcase_create("basics");

	suite_add_tcase(s, tc);
	tcase_add_test(tc, malloc_basic_small);
	tcase_add_test(tc, malloc_basic_med);
	tcase_add_test(tc, malloc_basic_big);
	return (s);
}
