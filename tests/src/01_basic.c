/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 00:12:46 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/22 00:49:57 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

START_TEST (malloc_basic_small)
{
	const char*	cs = "Hello World!";
	char*		s;

	if (!(s = malloc(13)))
		ck_abort_msg("malloc(13) failed!");
	memcpy(s, cs, 13);
	ck_assert(strcmp(s, cs) == 0);
	free(s);
}
END_TEST

START_TEST (malloc_basic_med)
{
	char		cs[512];
	char*		s;

	srand(time(NULL));
	for (int i = 0; i < 512; ++i)
		cs[i] = rand();
	if (!(s = malloc(512)))
		ck_abort_msg("malloc(512) failed!");
	memcpy(s, cs, 512);
	ck_assert(memcmp(s, cs, 512) == 0);
	free(s);
}
END_TEST

START_TEST (malloc_basic_big)
{
	unsigned char*	s;

	if (!(s = malloc(1024*1024)))
		ck_abort_msg("malloc(1024*1024) failed!");
	memset(s, 255, 1024*1024);
	for (int i = 0; i < 1024 * 1024; ++i)
		ck_assert(s[i] == 255);
	free(s);
}
END_TEST

Suite	*build_suite_01_basic(void)
{
	Suite	*s = suite_create("malloc_01_basic");
	TCase	*tc = tcase_create("basics");

	suite_add_tcase(s, tc);
	tcase_add_test(tc, malloc_basic_small);
	tcase_add_test(tc, malloc_basic_med);
	tcase_add_test(tc, malloc_basic_big);
	// tcase_add_test(tc, ft_strtrim_test_only_spaces);
	return (s);
}
