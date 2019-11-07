/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:54:47 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/11/07 15:14:06 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				display_file_list(t_file *file, t_len *lens)
{
	while (file)
	{
		if (!is_file_hidden(file))
		{
			if (g_opt.l)
				display_full_info(file, lens);
			else
				ft_putendl_buf(file->name);
		}
		file = file->next;
	}
}

void				display_file_tree(t_file *file, t_path *path)
{
	while (file)
	{
		if (file->child || file->err_open)
			display_folder(file, path, 0);
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

void				display_folder(t_file *file, t_path *path, int first)
{
	size_t			prevlen;

	prevlen = add_path_name(path, file->name);
	if ((!first || file->next) && is_openable(file, path->buf))
	{
		if (!first)
			ft_putchar_buf('\n');
		ft_putstr_buf(path->buf);
		ft_putstr_buf(":\n");
	}
	if (file->err_open)
		error_file(file->name, (int)file->err_open);
	else
	{
		if (g_opt.l && has_displayable(file) && !(file->isarg == e_isroot))
		{
			ft_putstr_buf("total ");
			ft_putnbr_buf(file->child_lens.total);
			ft_putchar_buf('\n');
		}
		display_file_list(file->child, &file->child_lens);
		display_file_tree(file->child, path);
	}
	remove_path_name(path, prevlen);
}
