/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_lots_cumulate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 23:05:30 by awoimbee          #+#    #+#             */
/*   Updated: 2019/10/11 20:48:34 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

START_TEST (malloc_lots_cumulate_small)
{
	char*		ptr[1000];

	for (int i = 0; i < 1000; ++i)
	{
		if (!(ptr[i] = my_malloc(128)))
			ck_abort_msg("malloc(128) failed, it should not have!");
		memcpy(ptr[i], str128, 128);
	}
	for (int i = 0; i < 1000; ++i)
	{
		ck_assert(memcmp(ptr[i], str128, 128) == 0);
		my_free(ptr[i]);
	}
}
END_TEST

START_TEST (malloc_lots_cumulate_med)
{
	char*		ptr[1000];

	for (int i = 0; i < 1000; ++i)
	{
		if (!(ptr[i] = my_malloc(512)))
			ck_abort_msg("malloc(128) failed, it should not have!");
		memcpy(ptr[i], str512, 512);
	}
	for (int i = 0; i < 1000; ++i)
	{
		ck_assert(memcmp(ptr[i], str512, 512) == 0);
		my_free(ptr[i]);
	}
}
END_TEST

START_TEST (malloc_lots_cumulate_big)
{
	char*		ptr[1000];

	for (int i = 0; i < 1000; ++i)
	{
		if (!(ptr[i] = my_malloc(1024 * 1024)))
			ck_abort_msg("malloc(1024 * 1024) number %d failed", i);
		for (char* ss = ptr[i]; ss < ptr[i] + (1024*1024); ss += 512)
			memcpy(ss, str512, 512);
	}
	for (int i = 0; i < 1000; ++i)
	{
		my_free(ptr[i]);
	}
}
END_TEST

Suite	*build_suite_03_lots_cumulate(void)
{
	Suite	*s = suite_create("03_lots_cumulate");
	TCase	*tc = tcase_create("lots of malloc accumulated and then lots of free");

	suite_add_tcase(s, tc);
	tcase_add_test(tc, malloc_lots_cumulate_small);
	tcase_add_test(tc, malloc_lots_cumulate_med);
	tcase_add_test(tc, malloc_lots_cumulate_big);
	return (s);
}
