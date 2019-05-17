/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:53:46 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/05/17 06:45:44 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				update_children(t_file *to)
{
	t_file			*child;

	child = to->child;
	while (child)
	{
		child->parent = to;
		child = child->next;
	}
}

void				move_data(t_file *from, t_file *to)
{
	to->name = from->name;
	to->namelen = from->namelen;
	to->gname = from->gname;
	to->perms = from->perms;
	to->owner = from->owner;
	to->xattr = from->xattr;
	to->links = from->links;
	to->total = from->total;
	to->size = from->size;
	to->date = from->date;
	to->flen = from->flen;
	to->dev = from->dev;
	to->child = from->child;
	to->isarg = from->isarg;
	to->isdir = from->isdir;
	to->err_open = from->err_open;
	to->err_stat = from->err_stat;
	to->target = from->target;
	update_children(to);
}

void				sort_list(t_file *head, t_cmp *f)
{
	t_file			*fast;
	t_file			*slow;
	t_file			tmp;

	if (!head || !head->next)
		return ;
	fast = head;
	slow = head->next;
	while (slow != NULL)
	{
		while (fast != slow)
		{
			if (f(slow, fast))
			{
				move_data(fast, &tmp);
				move_data(slow, fast);
				move_data(&tmp, slow);
			}
			fast = fast->next;
		}
		slow = slow->next;
		fast = head;
	}
}

int					compare_time(t_file *low, t_file *high)
{
	if (low->err_stat ^ high->err_stat)
		return (low->err_stat);
	if (low->date > high->date)
		return (!g_opt.r);
	else if (low->date < high->date)
		return (g_opt.r);
	if (ft_strncmp(low->name, high->name, low->namelen) < 0)
		return (!g_opt.r);
	return (g_opt.r);
}

int					compare_name(t_file *low, t_file *high)
{
	if (g_opt.l && low->err_stat ^ high->err_stat)
		return (low->err_stat);
	if (low->isarg)
	{
		if (low->isdir && !high->isdir)
			return (0);
		if (!low->isdir && high->isdir)
			return (1);
	}
	if (ft_strncmp(low->name, high->name, low->namelen) < 0)
		return (!g_opt.r);
	return (g_opt.r);
}
