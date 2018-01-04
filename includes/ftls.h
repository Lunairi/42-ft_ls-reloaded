/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mizukori250@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 09:00:00 by mlu               #+#    #+#             */
/*   Updated: 2017/08/25 09:00:00 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLS_H
# define FTLS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <string.h>

# include "libft.h"

typedef struct			s_data
{
	char				*file;
	char				*dir;
	char				*bits;
	int					mode;
	long long			blocks;
	int					nlinks;
	char				*uid;
	char				*gid;
	int					device;
	unsigned long long	size;
	long				mtime;
	long				nsec;
	long				sec;
	char				suffix;
	struct s_data		*next;
	struct s_data		*d;
}						t_data;

typedef struct			s_flags
{
	int					r;
	int					a;
	int					l;
	int					t;
	int					re;
	int					device;
	long long			blocks;
	int					endflag;
	int					sort;
	int					nlinks;
	int					uid;
	int					gid;
	unsigned int		major;
	unsigned int		minor;
	unsigned long long	size;
	unsigned long long	i;
	int					print;
	unsigned long long	total;
	unsigned long long	count;
	int					error;
	int					ac;
}						t_flags;

/*
** parse_input.c
*/
int						parse_dir(char *dir, t_flags *flags);
void					branch_dir_content(char *av, t_data **data,
							t_flags *flags);
void					set_one_arg(char *av, int ac, t_data **data,
							t_flags *flags);

/*
** parse_util.c
*/
char					*perms(int mode, t_flags *flags);
void					grab_data_length(t_data *data, t_flags *flags);
void					suffix(char *dir, t_data *data);
int						check_and_set_flags(char *str, t_flags *flags);

/*
** sort.c
*/
t_data					*sort_link_list(t_data *data,
							t_flags *flags, int loop);
t_data					*time_sort_link_list(t_data *data,
							t_flags *flags, int loop);

/*
** sort_util.c
*/
t_data					*swap_list(t_data *one, t_data *two, int *loop);
int						time_compare(t_data *one, t_data *two);

/*
** print.c
*/
void					print_list(t_data *data, t_flags *flags);
void					print_long(t_data *data, t_flags *flags);
void					print_recur(t_data *data, t_flags *flags);

/*
** print_util.c
*/
void					reset_flags(t_flags *flags);
void					print_behavior(t_data *data, t_flags *flags);
void					print_date_name(t_data *data, t_flags *flags);
void					grab_dir_data_length(t_data *data, t_flags *flags);

/*
** utility.c
*/
void					free_struct(t_data **data);
void					print_spacing(t_flags *flags);
void					print_xattr(t_flags *flags, char *mtime);
void					clear_buf(char *buf);

/*
** norminette.c
*/
void					set_more_list_elements(char *str, char *dir,
							t_data *data, t_flags *flags);
void					set_str_av(char **av, char **str);
void					reset_and_check_dir(t_flags *flags);
void					print_recur_dir(t_data *data, t_flags *flags,
							t_data *dir);
void					free_stuff(char *dir, t_data *new);

#endif
