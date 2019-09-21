/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 15:29:06 by awoimbee          #+#    #+#             */
/*   Updated: 2019/09/22 00:16:28 by awoimbee         ###   ########.fr       */
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

Suite	*build_suite_01_basic(void);

#endif
