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
	char				*bits;
	// long long			blocks;
	int					nlinks;
	char				*uid;
	char				*gid;
	unsigned int		major;
	unsigned int		minor;
	// int					device;
	unsigned long long	size;
	char				*mtime;
	struct s_data		*next;
	struct s_data		**dir;
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
	// int					nlinks;
	// int					uid;
	// int					gid;
	// unsigned int		major;
	// unsigned int		minor;
	// int					device;
	// unsigned long long	size;
	// unsigned long long	i;
	// int					exist;
	// int					file;
	// int					fnlinks;
	// int					fuid;
	// int					fgid;
	// unsigned long long	fsize;
	// unsigned int		fmajor;
	// unsigned int		fminor;
	// unsigned long long	total;
	// unsigned long long	count;
}						t_flags;

/*
** parse_input.c
*/
int		parse_input(int ac, char **av);

#endif
