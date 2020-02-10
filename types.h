/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 01:31:43 by lgarczyn          #+#    #+#             */
/*   Updated: 2020/02/10 20:38:01 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TYPES_H
# define _TYPES_H

typedef enum		e_type
{
	e_notdir = 0,
	e_isdir = 1,
}					t_type;

typedef enum		e_arg
{
	e_notarg = 0,
	e_isarg = 1,
}					t_arg;

typedef struct		s_len
{
	size_t			total;
	int				perm;
	int				links;
	int				owner;
	int				gname;
	int				size;
	int				dev;
}					t_len;

typedef struct		s_file
{
	struct s_file	*child;
	struct s_file	*next;
	struct s_len	child_lens;
	char			*name;
	char			*gname;
	char			*owner;
	char			*target;
	char			perms[11];
	char			xattr;
	size_t			links;
	size_t			size;
	time_t			date;
	dev_t			dev;
	int				err_open;
	int				err_stat;
	int				namelen;
	t_arg			isarg;
	t_type			isdir;
}					t_file;

typedef struct		s_path
{
	char			*buf;
	size_t			size;
	size_t			len;
}					t_path;

typedef struct		s_opt
{
	int				l:1;
	int				a:1;
	int				t:1;
	int				r:1;
	int				cr:1;
	int				o:1;
}					t_opt;

typedef struct		s_error
{
	int				return_value;
	char			*prog_name;
}					t_error;

typedef struct		s_print
{
	bool			first_block_printed;
	bool			multi_block;
}					t_print;

typedef struct stat	t_stat;

#endif
