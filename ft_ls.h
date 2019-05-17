/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 01:31:43 by lgarczyn          #+#    #+#             */
/*   Updated: 2019/05/17 12:31:16 by lgarczyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_LS_H
# define _FT_LS_H

# include <sys/xattr.h>
# include <sys/stat.h>
# include <stddef.h>
# include <string.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# include <stdio.h>
# include <errno.h>

# include "libft/includes/libft.h"

# define DISPLAY_BUFF_SIZE (4096 * 256)
# define PATH_BUFF_SIZE 4096
# define S_IRUSR 0000400
# define S_IWUSR 0000200
# define S_IXUSR 0000100
# define S_IRGRP 0000040
# define S_IWGRP 0000020
# define S_IXGRP 0000010
# define S_IROTH 0000004
# define S_IWOTH 0000002
# define S_IXOTH 0000001
# define SIX_MONTH (182 * 24 * 3600)

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


//simplify swap
typedef struct		s_file
{
	struct s_file	*parent;
	struct s_file	*child;
	struct s_file	*next;
	struct s_len	*flen;
	char			*name;
	char			*gname;
	char			*perms;
	char			*owner;
	char			*target;
	char			xattr;
	size_t			links;
	size_t			total;
	size_t			size;
	time_t			date;
	dev_t			dev;
	int				err_open;
	int				err_stat;
	int				namelen;
	t_arg			isarg;
	t_type			isdir;
}					t_file;

typedef struct		s_len
{
	int				perm;
	int				xattr;
	int				links;
	int				owner;
	int				gname;
	int				size;
	int				dev;
}					t_len;

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
}					t_opt;

typedef struct		s_error
{
	int				return_value;
	char			*prog_name;
}					t_error;

typedef struct stat	t_stat;

typedef int			(t_cmp)(t_file *, t_file *);

t_error				g_error;
t_opt				g_opt;

char				*get_linked_path(char *path);
int					is_file_hidden(t_file *file);
int					is_openable(t_file *file, char *path);

void				set_option(char opt);
int					analyze_options(int argc, char **argv);

void				*xmemalloc(size_t size);
void				*xmalloc(size_t size);

void				error_args(char opt);
void				error_memory(char *prog_name);
void				error_file(char *name, int err);

void				sort_list(t_file **head, t_cmp *f);
int					compare_time(t_file *low, t_file *high);
int					compare_name(t_file *low, t_file *high);

t_file				*new_node(char *const name);
void				add_node_to(t_file **alst, t_file *add);
void				add_child_to(t_file *alst, t_file *add);

t_path				*get_new_path(void);
int					set_path_name(t_path *path, char *name);
int					add_path_name(t_path *path, char *name);
void				remove_path_name(t_path *path, size_t prevlen);
void				try_realloc_path(t_path *path, size_t newlen);

void				free_file_tree(t_file *file);
t_file				*free_file(t_file *file);
void				free_path(t_path *path);
void				free_str(char *str);

t_file				*explore_all_files(char **av, t_path *path, t_cmp *f);
void				fill_file_perms(t_file *file, mode_t modes);
void				fill_file_info(t_file *file, char *path);
void				display_file_tree(t_file *file, t_path *path, int first);
void				display_full_info(t_file *file, t_len *len);

#endif
