/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 15:29:06 by awoimbee          #+#    #+#             */
/*   Updated: 2020/04/29 23:21:22 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <unistd.h>
# include <assert.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define PRTF_GRN "\e[32m"
# define PRTF_RED "\e[31m"
# define PRTF_EOC "\e[39m"

extern const char* str16;
extern const char* str64;
extern const char* str128;
extern const char* str512;

void	test_01_basic(void);
void	test_02_lots_basic(void);
void	test_03_lots_cumulate(void);
void	test_04_realloc(void);

#endif
