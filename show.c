/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:54:47 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/02 14:54:49 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				display_file_list(t_file *file)
{
	if (file == NULL)
		return ;
	if (!is_file_hidden(file))
	{
		if (g_opt.l)
			display_full_info(file, file->parent->flen);
		else
			ft_putendl_buf(file->name);
	}
	display_file_list(file->next);
}

int					has_displayable(t_file *file)
{
	file = file->child;
	while (file)
		if (is_file_hidden(file))
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
		if (g_opt.l && has_displayable(file))
		{
			ft_putstr_buf("total ");
			ft_putnbr_buf(file->total);
			ft_putchar_buf('\n');
		}
		display_file_list(file->child);
		display_file_tree(file->child, path, 0);
	}
	remove_path_name(path, prevlen);
}

void				display_file_tree(t_file *file, t_path *path, int first)
{
	if (!file)
		return ;
	if (file->child || file->err_open)
		display_folder(file, path, first);
	else if (file->isarg == e_isarg)
	{
		if (g_opt.l)
			display_full_info(file, file->parent->flen);
		else
			ft_putendl_buf(file->name);
	}
	display_file_tree(file->next, path, 0);
}
