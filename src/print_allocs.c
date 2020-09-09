/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_allocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:33:26 by awoimbee          #+#    #+#             */
/*   Updated: 2020/09/09 15:13:49 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intrin_malloc.h"

static void		sort_bins(void)
{
	t_bin	*b0;
	t_bin	*b1;
	t_bin	*tmp;

	b0 = (t_bin*)&g_bin;
	while (b0->next && b0->next->next)
	{
		b1 = b0;
		b0 = b0->next;
		if (b0->mem > b0->next->mem)
		{
			b1->next = b0->next;
			tmp = b1->next->next;
			b1->next->next = b0;
			b0->next = tmp;
			b0 = (t_bin*)&g_bin;
		}
	}
}

static size_t	itoa_hex(char *buff, size_t i)
{
	const char	dict[] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
	};
	size_t		len;
	size_t		tmp;

	len = 0;
	tmp = i;
	while (tmp)
	{
		++len;
		tmp /= 16;
	}
	buff[len] = '\0';
	tmp = len;
	while (i)
	{
		--tmp;
		buff[tmp] = dict[i % 16];
		i /= 16;
	}
	return (len);
}

static void		print_bin(t_bin *b, size_t elem_size)
{
	char		buf[17];
	int			i;

	i = -1;
	while (++i < BIN_SIZE)
	{
		if (!((b->used & ~any_bin()) & (get1() << i)))
			continue;
		write(1, "-->\t", 4);
		write(1, buf, itoa_hex(buf, elem_size));
		write(1, "\t", 1);
		write(1, buf, itoa_hex(buf, (size_t)(b->mem + (elem_size * i))));
		write(1, "\n", 1);
	}
}

static void		print_big_bin(t_bin *b)
{
	char		buf[17];

	write(1, "BIG\t", 4);
	write(1, buf, itoa_hex(buf, b->used & ~big_bin()));
	write(1, "\t", 1);
	write(1, buf, itoa_hex(buf, (size_t)b->mem));
	write(1, "\n", 1);
}

void __attribute__((visibility("default")))			print_allocs(void)
{
	t_bin		*b;

	sort_bins();
	b = (t_bin*)&g_bin;
	write(1, "CATEGORY\t|\tSIZE\t|\tADDRESS\n", 26);
	while (b->next)
	{
		b = b->next;
		if (b->used & big_bin())
		{
			print_big_bin(b);
			continue;
		}
		else if (b->used & med_bin())
		{
			write(1, "MED\n", 4);
			print_bin(b, g_bin.med_elem_size);
		}
		else if (b->used & sml_bin())
		{
			write(1, "SML\n", 4);
			print_bin(b, g_bin.sml_elem_size);
		}
	}
}
