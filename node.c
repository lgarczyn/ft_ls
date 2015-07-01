/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:57:43 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/02 14:57:52 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				add_child_to(t_file *alst, t_file *add)
{
	add->parent = alst;
	add_node_to(&(alst->child), add);
}

void				add_node_to(t_file **alst, t_file *add)
{
	t_file			*node;

	node = *alst;
	*alst = add;
	add->next = node;
}

t_file				*new_node(char *const name)
{
	t_file			*node;

	node = (t_file*)xmemalloc(sizeof(t_file));
	node->name = ft_strdup(name);
	node->namelen = ft_strlen(name);
	return (node);
}
