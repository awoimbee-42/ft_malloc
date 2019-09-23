/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 15:29:06 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/23 23:20:04 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <check.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <malloc.h>

# define PRTF_GRN "\e[32m"
# define PRTF_RED "\e[31m"
# define PRTF_EOC "\e[39m"

extern void*(*my_malloc)(size_t);
extern void(*my_free)(void*);
extern void*(*my_realloc)(void*, size_t);
extern void(*my_print_allocs)(void);
extern const char* str16;
extern const char* str64;
extern const char* str128;
extern const char* str512;

Suite	*build_suite_01_basic(void);
Suite	*build_suite_02_lots_basic(void);

#endif
