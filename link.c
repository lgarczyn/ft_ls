/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:58:58 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/11/11 06:45:36 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <limits.h>

char				*get_linked_path(char *path)
{
	static char		buffer[PATH_MAX];
	size_t			error;

	error = readlink(path, buffer, sizeof(buffer));
	if ((ssize_t)error == -1)
		return (NULL);
	buffer[error] = '\0';
	return (buffer);
}

int					is_openable(t_file *file, char *path)
{
	t_stat			st;
	char			*link;

	if (file->perms)
	{
		if (file->perms[0] == 'd')
			return (1);
		else if (file->perms[0] == 'l')
		{
			link = get_linked_path(path);
			if (!link)
				file->err_stat = errno;
			else
			{
				stat(link, &st);
				if (S_ISDIR(st.st_mode))
					return (1);
			}
		}
	}
	return (0);
}
