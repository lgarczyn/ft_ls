/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 05:11:38 by lgarczyn          #+#    #+#             */
/*   Updated: 2014/11/04 05:11:39 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_isspace(int c)
{
	if (c == ' ' || c == '\n')
		return (1);
	if (c == '\t' || c == '\f')
		return (1);
	if (c == '\v' || c == '\r')
		return (1);
	return (0);
}