/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:57:05 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/05/20 21:25:08 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void				fill_file_xattr(t_file *file, char *path)
{
	ssize_t			ret;
	acl_t			acl;
	acl_entry_t		entry;

	ret = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (ret > 0)
		file->xattr = '@';
	else
	{
		acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
		if (acl)
		{
			if (acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) > -1)
				file->xattr = '+';
			else
				file->xattr = ' ';
			acl_free(acl);
		}
		else
			file->xattr = ' ';
	}
}

void				fill_file_names(t_file *file, t_stat *st, t_len *len)
{
	struct group	*grp;
	struct passwd	*pwd;

	grp = getgrgid(st->st_gid);
	if (grp)
		file->gname = ft_strdup(grp->gr_name);
	else
		file->gname = ft_itoa(st->st_gid);
	len->gname = MAX((int)ft_strlen(file->gname), len->gname);
	pwd = getpwuid(st->st_uid);
	if (pwd)
		file->owner = ft_strdup(pwd->pw_name);
	else
		file->owner = ft_itoa(st->st_uid);
	len->owner = MAX((int)ft_strlen(file->owner), len->owner);
}

void				fill_file_specs(t_file *file, t_stat *st, t_len *len)
{
	file->date = st->st_mtimespec.tv_sec;
	file->size = st->st_size;
	file->dev = st->st_rdev;
	file->links = st->st_nlink;
	len->links = MAX(ft_intlen(file->links), len->links);
	if (file->perms[0] == 'c' || file->perms[0] == 'b')
		len->size = MAX(9, len->size);
	else
		len->size = MAX(ft_intlen(file->size), len->size);
}

void				fill_file_links(t_file *file, char *path)
{
	char			*link;

	if (file->perms[0] == 'l')
	{
		link = get_linked_path(path);
		if (link == NULL)
			file->err_stat = errno;
		else
			file->target = ft_strdup(link);
	}
}

void				fill_file_info(t_file *file, char *path)
{
	t_stat			st;
	t_len			*len;

	if (is_file_hidden(file) && !file->isarg)
		return ;
	if (file->parent && !file->parent->flen)
		file->parent->flen = (t_len*)xmemalloc(sizeof(t_len));
	if (lstat(path, &st) >= 0)
	{
		file->parent->total += st.st_blocks;
		len = file->parent->flen;
		fill_file_perms(file, st.st_mode);
		file->isdir = (file->perms[0] == 'd') ? e_isdir : e_notdir;
		if (!file->isarg || !file->isdir)
		{
			fill_file_xattr(file, path);
			fill_file_names(file, &st, len);
			fill_file_specs(file, &st, len);
			fill_file_links(file, path);
		}
	}
	else
		file->err_stat = errno;
}
