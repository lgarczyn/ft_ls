/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:53:46 by lgarczyn          #+#    #+#             */
/*   Updated: 2020/02/10 18:26:16 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			insert(t_file **list, t_file *file, t_cmp *f)
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
	t_file			*last;

	prev = *head;
	if (!prev)
		return ;
	list = prev->next;
	prev->next = NULL;
	*head = prev;
	last = prev;
	while (list)
	{
		prev = list;
		list = list->next;
		if (f(last, prev))
		{
			prev->next = NULL;
			last->next = prev;
			last = prev;
		}
		else
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
	if (ft_strcmp(low->name, high->name) < 0)
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
	if (ft_strcmp(low->name, high->name) < 0)
		return (!g_opt.r);
	return (g_opt.r);
}
