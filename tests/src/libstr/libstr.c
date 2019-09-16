/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 11:45:11 by awoimbee          #+#    #+#             */
/*   Updated: 2019/08/21 14:02:55 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check.h>
#include "libstr.h"

void		build_tests_libstr(SRunner *sr)
{
	srunner_add_suite(sr, build_suite_ft_strtrim());
}
