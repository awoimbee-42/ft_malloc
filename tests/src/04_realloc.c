/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 00:12:46 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/04 00:59:01 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void realloc_basic()
{
	char*		s;

	assert((s = malloc(1)));
	size_t i;
	for(i = 0; i < 400096; ++i) {
		assert((s = realloc(s, i + 2)) != NULL);
		s[i] = 'a';
		s[i + 1] = '\0';
		if (strlen(s) != i+1) {
			printf(
				"strlen(s) is: %lu instead of %lu\n",
				i+1,
				strlen(s)
			);
			printf("\n%s\n", &s[i+1]);
			fflush(stdout);
			assert(0);
		}
	}
	assert(strlen(s) == i);
	while (--i) {
		assert(s[i] == 'a');
	}
	free(s);
}


void test_04_realloc(void)
{
	write(1, "realloc_basic...\n", 17);
	realloc_basic();
}
