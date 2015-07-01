/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 18:58:24 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/09 18:58:41 by lgarczyn         ###   ########.fr       */
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

void				set_perms(char *perms, mode_t modes)
{
	perms[0] = get_type(modes);
	perms[1] = (modes & S_IRUSR) ? 'r' : '-';
	perms[2] = (modes & S_IWUSR) ? 'w' : '-';
	if (modes & S_ISUID)
		perms[3] = (modes & S_IXUSR) ? 's' : 'S';
	else
		perms[3] = (modes & S_IXUSR) ? 'x' : '-';
	perms[4] = (modes & S_IRGRP) ? 'r' : '-';
	perms[5] = (modes & S_IWGRP) ? 'w' : '-';
	if (modes & S_ISGID)
		perms[6] = (modes & S_IXGRP) ? 's' : 'S';
	else
		perms[6] = (modes & S_IXGRP) ? 'x' : '-';
	perms[7] = (modes & S_IROTH) ? 'r' : '-';
	perms[8] = (modes & S_IWOTH) ? 'w' : '-';
	if (modes & S_ISVTX)
		perms[9] = (modes & S_IXOTH) ? 't' : 'T';
	else
		perms[9] = (modes & S_IXOTH) ? 'x' : '-';
	perms[10] = '\0';
}

void				fill_file_perms(t_file *file, mode_t modes)
{
	file->perms = xmalloc(11);
	set_perms(file->perms, modes);
}
