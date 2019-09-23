/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_lots_basic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 23:05:30 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/23 23:35:51 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

START_TEST (malloc_lots_basic_small)
{
	char*		s;

	for (int i = 0; i < 1000; ++i)
	{
		if (!(s = my_malloc(128)))
			ck_abort_msg("malloc(128) failed, it should not have!");
		memcpy(s, str128, 128);
		ck_assert(memcmp(s, str128, 128) == 0);
		my_free(s);
	}
}
END_TEST

START_TEST (malloc_lots_basic_med)
{
	char*		s;

	for (int i = 0; i < 1000; ++i)
	{
		if (!(s = my_malloc(512)))
			ck_abort_msg("malloc(512) failed!");
		memcpy(s, str512, 512);
		ck_assert(memcmp(s, str512, 512) == 0);
		my_free(s);
	}
}
END_TEST

START_TEST (malloc_lots_basic_big)
{
	char*		s;

	for (int i = 0; i < 1000; ++i)
	{
		if (!(s = my_malloc(1024 * 1024)))
			ck_abort_msg("malloc(1024 * 1024) failed!");
		for (char* ss = s; ss < s + (1024*1024); ss += 512)
			memcpy(ss, str512, 512);
		for (char* ss = s; ss < s + (1024*1024); ss += 512)
			ck_assert(memcmp(ss, str512, 512) == 0);
		my_free(s);
	}
}
END_TEST

Suite	*build_suite_02_lots_basic(void)
{
	Suite	*s = suite_create("02_lots_basic");
	TCase	*tc = tcase_create("lots of malloc, lots of free");

	suite_add_tcase(s, tc);
	tcase_add_test(tc, malloc_lots_basic_small);
	tcase_add_test(tc, malloc_lots_basic_med);
	tcase_add_test(tc, malloc_lots_basic_big);
	return (s);
}
