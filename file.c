/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:58:58 by lgarczyn          #+#    #+#             */
/*   Updated: 2020/02/10 21:30:39 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool	is_file_hidden(t_file *file)
{
	if (file->name[0] == '.' && !g_opt.a && !file->isarg)
		return (true);
	return (false);
}

bool	should_get_file_children(t_file *file)
{
	if (!g_opt.cr && !file->isarg)
		return (false);
	if (file->err_stat)
		return (false);
	if (file->isdir == false)
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

void	get_file_children(t_file *file, t_path *path)
{
	size_t		prevlen;
	t_file		*child;
	DIR			*dir;
	int			dir_fd;
	t_dirent	*entry;

	dir = opendir(path->buf);
	if (dir == NULL)
	{
		file->err_open = errno;
		return ;
	}
	dir_fd = g_opt.o ? dirfd(dir) : 0;
	while ((entry = readdir(dir)) != NULL)
		add_child_to(file, new_node(entry->d_name));
	child = file->child;
	while (child)
	{
		prevlen = add_path_name(path, child->name);
		fill_file_info(child, dir_fd, path->buf, &file->child_lens);
		remove_path_name(path, prevlen);
		child = child->next;
	}
	closedir(dir);
}

void	explore_display_file(t_file *file, t_len *lens, t_path *path, t_cmp *f)
{
	t_file	*prev;
	size_t	prevlen;

	display_file_list(file, lens);
	while (file)
	{
		if (should_get_file_children(file))
		{
			prevlen = add_path_name(path, file->name);
			get_file_children(file, path);
			sort_list(&file->child, f);
			display_folder(file, path->buf);
			explore_display_file(file->child, &file->child_lens, path, f);
			remove_path_name(path, prevlen);
		}
		prev = file;
		file = file->next;
		free_file(prev);
	}
}

void	explore_args(int ac, char **av, t_path *path, t_cmp *f)
{
	t_file	*file;
	t_file	*node;
	int		i;
	t_len	lens;

	i = 0;
	if (ac == 0)
	{
		av[0] = ".";
		ac = 1;
	}
	file = NULL;
	ft_bzero(&lens, sizeof(t_len));
	while (i < ac)
	{
		add_path_name(path, av[i]);
		node = new_node(av[i]);
		add_node_to(&file, node);
		node->isarg = e_isarg;
		fill_file_info(node, 0, path->buf, &lens);
		remove_path_name(path, 0);
		i++;
	}
	sort_list(&file, compare_name);
	explore_display_file(file, &lens, path, f);
}
