/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:51:47 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/02 14:51:49 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path				*get_new_path(void)
{
	t_path			*path;

	path = (t_path*)xmalloc(sizeof(t_path));
	path->buf = xmalloc(PATH_BUFF_SIZE);
	path->size = PATH_BUFF_SIZE;
	path->len = 0;
	return (path);
}

int					add_path_name(t_path *path, char *name)
{
	size_t			newlen;
	size_t			prevlen;

	prevlen = path->len;
	newlen = prevlen + ft_strlen(name) + (prevlen != 0);
	try_realloc_path(path, newlen);
	if (prevlen)
		path->buf[prevlen] = '/';
	ft_strcpy(path->buf + prevlen + (prevlen != 0), name);
	path->len = newlen;
	return (prevlen);
}

void				remove_path_name(t_path *path, size_t prevlen)
{
	path->len = prevlen;
	path->buf[prevlen] = '\0';
}

void				try_realloc_path(t_path *path, size_t newlen)
{
	char			*buf;

	if (path->size > newlen)
		return ;
	while (path->size <= newlen)
		path->size *= 2;
	buf = (char*)xmalloc(path->size);
	ft_strcpy(path->buf, buf);
}
