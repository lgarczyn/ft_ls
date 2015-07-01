/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:56:11 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/02 14:56:23 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				error_file(char *name, int err)
{
	ft_reset_buf(STDERR);
	ft_putstr_buf(g_error.prog_name);
	ft_putstr_buf(": ");
	ft_putstr_buf(name);
	ft_putstr_buf(": ");
	ft_putstr_buf(strerror(err));
	ft_putchar_buf('\n');
	ft_reset_buf(STDOUT);
}

void				error_args(char opt)
{
	ft_reset_buf(STDERR);
	ft_putstr_buf(g_error.prog_name);
	ft_putstr_buf(": illegal option -- ");
	ft_putchar_buf(opt);
	ft_putstr_buf("\nusage: ./ft_ls [-Ralrt] [file ...]\n");
	ft_flush_buf();
	exit(2);
}

void				error_memory(char *prog_name)
{
	ft_flush_buf();
	if (prog_name)
		perror(prog_name);
	else
		perror(g_error.prog_name);
	exit(2);
}

void				*xmalloc(size_t size)
{
	void			*mem;

	mem = (void*)malloc(size);
	if (mem)
		return (mem);
	error_memory(NULL);
	exit(2);
}

void				*xmemalloc(size_t size)
{
	void			*mem;

	mem = xmalloc(size);
	return (ft_memset(mem, '\0', size));
}
