/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 00:12:46 by awoimbee          #+#    #+#             */
/*   Updated: 2020/04/30 11:35:06 by awoimbee         ###   ########.fr       */
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
