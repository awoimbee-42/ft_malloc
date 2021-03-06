/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isempty.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:57:27 by awoimbee          #+#    #+#             */
/*   Updated: 2020/03/06 00:28:04 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/t_queue.h>

int			que_isempty(const t_queue *que)
{
	if (que->start == -1)
		return (1);
	return (0);
}
