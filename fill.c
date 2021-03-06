/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:57:05 by lgarczyn          #+#    #+#             */
/*   Updated: 2020/02/10 20:37:01 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void		set_max_val(int current_len, int *max_len)
{
	if (current_len > *max_len)
		*max_len = current_len;
}

void		fill_file_xattr(t_file *file, char *path)
{
	ssize_t			ret;
	acl_t			acl;
	acl_entry_t		entry;

	ret = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	file->xattr = ' ';
	if (ret > 0)
	{
		file->xattr = '@';
		return ;
	}
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl)
	{
		if (acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) > -1)
			file->xattr = '+';
		else
			file->xattr = ' ';
		acl_free(acl);
	}
}

void		fill_file_names(t_file *file, t_stat *st, t_len *len, char *path)
{
	struct group	*grp;
	struct passwd	*pwd;
	char			*link;

	grp = getgrgid(st->st_gid);
	if (grp)
		file->gname = ft_strdup(grp->gr_name);
	else
		file->gname = ft_itoa(st->st_gid);
	set_max_val(ft_strlen(file->gname), &len->gname);
	pwd = getpwuid(st->st_uid);
	if (pwd)
		file->owner = ft_strdup(pwd->pw_name);
	else
		file->owner = ft_itoa(st->st_uid);
	set_max_val(ft_strlen(file->owner), &len->owner);
	if (file->perms[0] == 'l')
	{
		link = get_linked_path(path);
		if (link == NULL)
			file->err_stat = errno;
		else
			file->target = ft_strdup(link);
	}
}

void		fill_file_specs(t_file *file, t_stat *st, t_len *len)
{
	file->date = st->st_mtimespec.tv_sec;
	file->size = st->st_size;
	file->dev = st->st_rdev;
	file->links = st->st_nlink;
	set_max_val(ft_intlen(file->links), &len->links);
	if (file->perms[0] == 'c' || file->perms[0] == 'b')
		set_max_val(9, &len->size);
	else
		set_max_val(ft_intlen(file->size), &len->size);
}

void		fill_file_info(t_file *file, int dir_fd, char *path, t_len *len)
{
	t_stat	st;
	int		r;

	if (is_file_hidden(file))
		return ;
	if (dir_fd)
		r = fstatat(dir_fd, file->name, &st, 0);
	else
		r = lstat(path, &st);
	if (r >= 0)
	{
		len->total += st.st_blocks;
		fill_file_perms(file, st.st_mode);
		file->isdir = (file->perms[0] == 'd') ? e_isdir : e_notdir;
		if (g_opt.t == false && g_opt.l == false)
			return ;
		fill_file_specs(file, &st, len);
		if (g_opt.l == false)
			return ;
		fill_file_xattr(file, path);
		fill_file_names(file, &st, len, path);
	}
	else
		file->err_stat = errno;
}
