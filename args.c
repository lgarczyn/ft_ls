/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 14:59:38 by lgarczyn          #+#    #+#             */
/*   Updated: 2020/02/10 18:37:52 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					analyze_options(int ac, char **av)
{
	int				i;
	int				j;

	g_error.return_value = 0;
	g_error.prog_name = av[0];
	i = 0;
	while (++i < ac)
	{
		if (av[i][0] != '-')
			return (i);
		if (av[i][1] == '\0')
			return (i);
		if (av[i][1] == '-' && !av[i][2])
			return (i + 1);
		j = 0;
		while (av[i][++j])
			set_option(av[i][j]);
	}
	return (i);
}

void				set_option(char opt)
{
	if (opt == 'l')
		g_opt.l = 1;
	else if (opt == 'R')
		g_opt.cr = 1;
	else if (opt == 'a')
		g_opt.a = 1;
	else if (opt == 'r')
		g_opt.r = 1;
	else if (opt == 't')
		g_opt.t = 1;
	else if (opt == '1')
		g_opt.l = 0;
	else if (opt == 'o')
		g_opt.o = 1;
	else
		error_args(opt);
}
