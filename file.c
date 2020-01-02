/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:58:58 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/11/11 06:54:08 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool				is_file_hidden(t_file *file)
{
	if (file->name[0] == '.' && !g_opt.a && !file->isarg)
		return (true);
	return (false);
}

bool				should_get_file_children(t_file *file)
{
	if (!g_opt.cr && !file->isarg)
		return (false);
	if (!file->perms || file->err_stat)
		return (false);
	if (file->perms[0] != 'd')
		return (false);
	if (file->isarg)
		return (true);
	if (file->name[0] != '.')
		return (true);
	if (file->name[1] == '\0')
		return (false);
	if (file->name[1] != '.')
		return (true);
	if (file->name[2] == '\0')
		return (false);
	return (true);
}

void				get_file_children(t_file *file, t_path *path)
{
	size_t			prevlen;
	t_file			*child;
	DIR				*dir;
	struct dirent	*entry;

	if ((dir = opendir(path->buf)))
	{
		while ((entry = readdir(dir)) != NULL)
			add_child_to(file, new_node(entry->d_name));
		closedir(dir);
		child = file->child;
		while (child)
		{
			prevlen = add_path_name(path, child->name);
			fill_file_info(child, path->buf, &file->child_lens);
			remove_path_name(path, prevlen);
			child = child->next;
		}
	}
	else
		file->err_open = errno;
}

#include <stdio.h>

void				explore_display_file(t_file *file, t_path *path, t_cmp *f)
{
	t_file			*child;
	t_file			*prev;
	size_t			prevlen;

	sort_list(&file->child, f);
	display_folder(file, path->buf);
	g_print_info.first_block_printed = true;
	child = file->child;
	while (child)
	{
		if (should_get_file_children(child))
		{
			prevlen = add_path_name(path, child->name);
			get_file_children(child, path);
			explore_display_file(child, path, f);
			remove_path_name(path, prevlen);
		}
		prev = child;
		child = child->next;
		free_file(prev);
	}
	file->child = NULL;
}

void				explore_base_dir(t_path *path, t_cmp *f)
{
	t_file			*file;

	g_print_info.single_block = true;
	file = new_node(".");
	file->isarg = true;
	add_path_name(path, ".");
	get_file_children(file, path);
	explore_display_file(file, path, f);
	remove_path_name(path, 0);
	free_file(file);
}

void				explore_all_files(char **av, t_path *path, t_cmp *f)
{
	t_file			*file;
	t_file			*node;
	int				i;

	i = 0;
	if (!av[i])
		return (explore_base_dir(path, f));
	if (!av[i + 1])
		g_print_info.single_block = true;
	file = new_node("");
	while (av[i])
	{
		add_path_name(path, av[i]);
		node = new_node(av[i]);
		add_child_to(file, node);
		node->isarg = e_isarg;
		fill_file_info(node, path->buf, &file->child_lens);
		remove_path_name(path, 0);
		i++;
	}
	explore_display_file(file, path, f);
	free_file(file);
}
