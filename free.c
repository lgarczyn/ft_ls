/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:55:16 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/02 14:55:29 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				free_str(char *str)
{
	if (str)
		free(str);
}

void				free_path(t_path *path)
{
	free(path->buf);
	free(path);
}

t_file				*free_file(t_file *file)
{
	t_file			*node;

	node = file->next;
	free_str(file->name);
	free_str(file->gname);
	free_str(file->perms);
	free_str(file->owner);
	if (file->flen)
		free(file->flen);
	free(file);
	return (node);
}

void				free_file_tree(t_file *file)
{
	while (file)
	{
		if (file->child)
			free_file_tree(file->child);
		file = free_file(file);
	}
}
