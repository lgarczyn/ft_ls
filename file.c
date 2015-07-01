/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:58:58 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/02 14:59:06 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					is_file_hidden(t_file *file)
{
	if (file->name[0] == '.' && !g_opt.a)
		return (1);
	return (0);
}

int					should_explore_file(t_file *file)
{
	if (!file->perms)
		return (0);
	if (file->perms[0] != 'd')
		return (0);
	if (file->name[0] != '.')
		return (1);
	if (file->name[1] == '\0')
		return (0);
	if (file->name[1] != '.')
		return (1);
	if (file->name[2] == '\0')
		return (0);
	return (1);
}

void				explore_file(t_file *file, t_path *path, t_cmp *f)
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
			fill_file_info(child, path->buf);
			if (g_opt.cr && should_explore_file(child))
				explore_file(child, path, f);
			child = child->next;
			remove_path_name(path, prevlen);
		}
		sort_list(file->child, f);
	}
	else
		file->err_open = errno;
}

t_file				*explore_base_dir(t_path *path, t_cmp *f)
{
	t_file			*file;

	file = NULL;
	add_path_name(path, ".");
	add_node_to(&file, new_node("."));
	explore_file(file, path, f);
	remove_path_name(path, 0);
	return (file);
}

t_file				*explore_all_files(char **av, t_path *path, t_cmp *f)
{
	t_file			*file;
	t_file			*node;
	int				i;

	i = 0;
	if (!av[i])
		return (explore_base_dir(path, f));
	file = new_node("");
	while (av[i])
	{
		add_path_name(path, av[i]);
		node = new_node(av[i]);
		add_node_to(&(file->child), node);
		node->isarg = e_isarg;
		node->parent = file;
		fill_file_info(node, path->buf);
		if (is_openable(node, node->name))
			explore_file(node, path, f);
		remove_path_name(path, 0);
		i++;
	}
	return (file->child);
}
