/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 01:31:30 by lgarczyn          #+#    #+#             */
/*   Updated: 2020/02/10 21:47:13 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					main(int ac, char **av)
{
	int				start;
	t_path			*path;
	char			buffer[DISPLAY_BUFF_SIZE];
	t_cmp			*cmp;

	ft_buf(buffer, DISPLAY_BUFF_SIZE, STDOUT);
	start = analyze_options(ac, av);
	path = get_new_path();
	cmp = g_opt.t ? compare_time : compare_name;
	if (ac - start > 1)
		g_print_info.multi_block = true;
	explore_args(ac - start, av + start, path, cmp);
	ft_flush_buf();
	free_path(path);
	return (g_error.return_value);
}
