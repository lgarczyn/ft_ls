/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 01:31:30 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/05/17 12:32:44 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					main(int ac, char **av)
{
	int				start;
	int				ret;
	t_file			*files;
	t_path			*path;
	char			buffer[DISPLAY_BUFF_SIZE];

	ft_buf(buffer, DISPLAY_BUFF_SIZE, STDOUT);
	start = analyze_options(ac, av);
	path = get_new_path();
	if (g_opt.t)
	{
		files = explore_all_files(av + start, path, compare_time);
		sort_list(&files, compare_time);
	}
	else
	{
		files = explore_all_files(av + start, path, compare_name);
		sort_list(&files, compare_name);
	}
	display_file_tree(files, path, 1);
	ft_flush_buf();
	ret = g_error.return_value;
	free_path(path);
	free_file_tree(files->parent);
	return (ret);
}
