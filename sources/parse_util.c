/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

/*
** Function: check_and_set_flags
** This function checks the passed string to see if it contained any of the
** flags that is supported by ls. If so it will set the t_flags struct to 1
** which will later be used to manipulate the printing output.
** Otherwise if it's not valid
** then it will print an error message. I know this is mimicing ubuntu/linux ls
** instead of mac ls but I started this originally on a linux OS and like the
** format of this more than the mac version.
*/

int		check_and_set_flags(char *str, t_flags *flags)
{
	int i;

	i = 0;
	while (str[++i] != '\0')
	{
		str[i] == 'r' ? flags->r = 1 : 0;
		str[i] == 'a' ? flags->a = 1 : 0;
		str[i] == 'l' ? flags->l = 1 : 0;
		str[i] == 't' ? flags->t = 1 : 0;
		str[i] == 'R' ? flags->re = 1 : 0;
		str[i] == '1' ? flags->l = 0 : 0;
		if (str[i] != 'r' && str[i] != 'a' && str[i] != '1'
			&& str[i] != 'l' && str[i] != 't' && str[i] != 'R')
		{
			ft_printf("ft_ls: illegal option -- %c\n", str[i]);
			ft_printf("usage: ls [-alrRt1] [file ...]\n");
			ft_printf("Try 'ft_ls --help' for more information.\n");
			flags->error = 1;
			return (1);
		}
	}
	return (0);
}

/*
** Function: suffix
** This function grabs the extended attribute values for
** diff files and will suffix it to the end of the bits later
** during printing.
*/

void	suffix(char *dir, t_data *data)
{
	acl_t			acl;
	acl_entry_t		tmp;

	acl = acl_get_link_np(dir, ACL_TYPE_EXTENDED);
	acl_get_entry(acl, ACL_FIRST_ENTRY, &tmp);
	acl_free(acl);
	acl = 0;
	if (listxattr(dir, 0, 0, 0) > 0)
		data->suffix = '@';
	else if (acl != 0)
		data->suffix = '+';
	else
		data->suffix = ' ';
}

/*
** Function: grab_data_length
** This function is used to grab the length of each information stored
** to help with formatting when time comes for printing.
*/

void	grab_data_length(t_data *data, t_flags *flags)
{
	flags->blocks = flags->blocks + data->blocks;
	if (ft_strlen(data->uid) > flags->uid)
		flags->uid = ft_strlen(data->uid);
	if (ft_strlen(data->gid) > flags->gid)
		flags->gid = ft_strlen(data->gid);
	if (ft_numullen(data->size) > flags->size)
		flags->size = ft_numullen(data->size);
	if (ft_numlen(data->nlinks) > flags->nlinks)
		flags->nlinks = ft_numlen(data->nlinks);
	if (ft_numlen(major(data->device)) > flags->major)
		flags->major = ft_numlen(major(data->device));
	if (ft_numlen(minor(data->device)) > flags->minor)
		flags->minor = ft_numlen(minor(data->device));
}

/*
** Function: file_type
** This function is to help determine what type of mode the
** content that is being passed in is. It also will check for
** content that is is a block (b) and (c) type, which will require
** major and minor devices to be displayed.
*/

static int	file_type(int mode, t_flags *flags)
{
	char	c;

	if (S_ISREG(mode))
		c = '-';
	else if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISBLK(mode))
	{
		flags->device = 1;
		c = 'b';
	}
	else if (S_ISCHR(mode))
	{
		flags->device = 1;
		c = 'c';
	}
	else if (S_ISFIFO(mode))
		c = 'p';
	else if (S_ISLNK(mode))
		c = 'l';
	else if (S_ISSOCK(mode))
		c = 's';
	else
		c = '?';
	return (c);
}

/*
** Function: perms
** This function takes the mode passed in and parses the information
** from it using macros and bit shifting. This way we can get the
** permissions stored into bits and pass it back.
*/

char		*perms(int mode, t_flags *flags)
{
	static const char	*rwx[] = {"---", "--x", "-w-", "-wx",
		"r--", "r-x", "rw-", "rwx"};
	static char			bits[11];

	bits[0] = file_type(mode, flags);
	ft_strcpy(&bits[1], rwx[(mode >> 6) & 7]);
	ft_strcpy(&bits[4], rwx[(mode >> 3) & 7]);
	ft_strcpy(&bits[7], rwx[(mode & 7)]);
	if (mode & S_ISUID)
		bits[3] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		bits[6] = (mode & S_IXGRP) ? 's' : 'l';
	if (mode & S_ISVTX)
		bits[9] = (mode & S_IXOTH) ? 't' : 'T';
	bits[10] = '\0';
	return (bits);
}
