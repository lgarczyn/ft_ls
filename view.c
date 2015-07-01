/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 19:45:21 by lgarczyn          #+#    #+#             */
/*   Updated: 2015/05/09 19:46:45 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				display_date(time_t date)
{
	time_t			curtime;
	char			*datestr;
	int				len;

	time(&curtime);
	datestr = ctime(&date) + 4;
	if (date > curtime || date + SIX_MONTH <= curtime)
	{
		ft_putnstr_buf(datestr, 7);
		ft_putchar_buf(' ');
		datestr += 16;
		len = 0;
		while (*datestr == ' ')
			datestr++;
		while (datestr[len] >= '0' && datestr[len] <= '9')
			len++;
		ft_putnstr_buf(datestr, len);
	}
	else
		ft_putnstr_buf(datestr, 12);
}

void				display_size(t_file *file, t_len *len)
{
	if (file->perms && (file->perms[0] == 'c' || file->perms[0] == 'b'))
	{
		ft_putspace_buf(len->size - 5 - ft_intlen(major(file->dev)));
		ft_putnbr_buf(major(file->dev));
		ft_putchar_buf(',');
		ft_putspace_buf(4 - ft_intlen(minor(file->dev)));
		ft_putnbr_buf(minor(file->dev));
	}
	else
	{
		ft_putspace_buf(len->size + 1 - ft_intlen(file->size));
		ft_putnbr_buf(file->size);
	}
}

void				display_link(t_file *file)
{
	if (file->target)
	{
		ft_putstr_buf(" -> ");
		ft_putstr_buf(file->target);
	}
}

void				display_full_info(t_file *file, t_len *len)
{
	if (!file->err_stat)
	{
		ft_putstr_buf(file->perms);
		ft_putchar_buf(file->xattr);
		ft_putspace_buf(len->links + 1 - ft_intlen(file->links));
		ft_putnbr_buf(file->links);
		ft_putspace_buf(1);
		ft_putstr_buf(file->owner);
		ft_putspace_buf(len->owner + 2 - ft_strlen(file->owner));
		ft_putstr_buf(file->gname);
		ft_putspace_buf(len->gname + 1 - ft_strlen(file->gname));
		display_size(file, len);
		ft_putspace_buf(1);
		display_date(file->date);
		ft_putspace_buf(1);
		ft_putstr_buf(file->name);
		display_link(file);
		ft_putchar_buf('\n');
	}
	else
		error_file(file->name, (int)file->err_stat);
}
