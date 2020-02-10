/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:54:47 by lgarczyn          #+#    #+#             */
/*   Updated: 2020/02/10 19:36:26 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				display_file_list(t_file *file, t_len *lens)
{
	while (file)
	{
		if (!is_file_hidden(file) && !(file->isarg && file->perms[0] == 'd'))
		{
			if (g_opt.l)
				display_full_info(file, lens);
			else
				ft_putendl_buf(file->name);
		}
		file = file->next;
	}
}

int					has_displayable(t_file *file)
{
	file = file->child;
	while (file)
		if (is_file_hidden(file) || file->err_open || file->err_stat)
			file = file->next;
		else
			return (1);
	return (0);
}

void				display_folder(t_file *file, char *path)
{
	if (g_print_info.first_block_printed == true)
		ft_putchar_buf('\n');
	g_print_info.first_block_printed = true;
	if (g_print_info.single_block == false && is_openable(file, path))
	{
		ft_putstr_buf(path);
		ft_putstr_buf(":\n");
	}
	g_print_info.single_block = false;
	if (file->err_open)
		error_file(file->name, (int)file->err_open);
	else
	{
		if (g_opt.l && has_displayable(file) && (file->child_lens.total || !file->isarg))
		{
			ft_putstr_buf("total ");
			ft_putnbr_buf(file->child_lens.total);
			ft_putchar_buf('\n');
		}
		display_file_list(file->child, &file->child_lens);
	}
}
