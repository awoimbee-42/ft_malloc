/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:39:13 by awoimbee          #+#    #+#             */
/*   Updated: 2020/07/17 00:50:54 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/types.h>

void			free_all(void);
void			free(void *ptr);
void			*malloc(size_t size);
void			*calloc(size_t nmemb, size_t size);
void			*reallocarray(void *ptr, size_t nmemb, size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);
void			print_allocs(void);

#endif
