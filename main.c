/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 01:31:30 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/11/11 05:20:10 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					main(int ac, char **av)
{
	int				start;
	t_path			*path;
	char			buffer[DISPLAY_BUFF_SIZE];

	time(&g_time);
	ft_buf(buffer, DISPLAY_BUFF_SIZE, STDOUT);
	start = analyze_options(ac, av);
	path = get_new_path();
	if (g_opt.t)
	{
		explore_all_files(av + start, path, compare_time);
	}
	else
	{
		explore_all_files(av + start, path, compare_name);
	}
	ft_flush_buf();
	free_path(path);
	return (g_error.return_value);
}
