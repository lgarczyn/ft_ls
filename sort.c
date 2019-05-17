/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:53:46 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/05/17 12:54:36 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


void				insert(t_file **list, t_file *file, t_cmp *f)
{
	while (*list && f(*list, file))
	{
		list = &(*list)->next;
	}
	file->next = *list;
	*list = file;
}

void				sort_list(t_file **head, t_cmp *f)
{
	t_file			*list;
	t_file			*prev;

	list = *head;
	*head = NULL;
	while (list)
	{
		prev = list;
		list = list->next;
		insert(head, prev, f);
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
