/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 18:58:24 by lgarczyn          #+#    #+#             */
/*   Updated: 2020/02/10 19:36:06 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char				get_type(mode_t modes)
{
	if (S_ISBLK(modes))
		return ('b');
	if (S_ISCHR(modes))
		return ('c');
	if (S_ISDIR(modes))
		return ('d');
	if (S_ISLNK(modes))
		return ('l');
	if (S_ISSOCK(modes))
		return ('s');
	if (S_ISFIFO(modes))
		return ('p');
	return ('-');
}

void				fill_file_perms(t_file *file, mode_t modes)
{
	file->perms[0] = get_type(modes);
	file->perms[1] = (modes & S_IRUSR) ? 'r' : '-';
	file->perms[2] = (modes & S_IWUSR) ? 'w' : '-';
	if (modes & S_ISUID)
		file->perms[3] = (modes & S_IXUSR) ? 's' : 'S';
	else
		file->perms[3] = (modes & S_IXUSR) ? 'x' : '-';
	file->perms[4] = (modes & S_IRGRP) ? 'r' : '-';
	file->perms[5] = (modes & S_IWGRP) ? 'w' : '-';
	if (modes & S_ISGID)
		file->perms[6] = (modes & S_IXGRP) ? 's' : 'S';
	else
		file->perms[6] = (modes & S_IXGRP) ? 'x' : '-';
	file->perms[7] = (modes & S_IROTH) ? 'r' : '-';
	file->perms[8] = (modes & S_IWOTH) ? 'w' : '-';
	if (modes & S_ISVTX)
		file->perms[9] = (modes & S_IXOTH) ? 't' : 'T';
	else
		file->perms[9] = (modes & S_IXOTH) ? 'x' : '-';
	file->perms[10] = '\0';
}
