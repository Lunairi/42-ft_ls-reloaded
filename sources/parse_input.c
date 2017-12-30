/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

/*
** Looks like this gets the size value of all data for printing?
** Fuck I don't remember why I wrote this LOL
*/
// void	grab_format_long(char *str, char *dir, char *file, t_flags *flags)
// {
// 	struct stat		items;
// 	struct passwd	user;
// 	struct group	group;

// 	if (dir != NULL && str != NULL)
// 	{
// 		file = ft_strjoin(dir, "/");
// 		file = ft_strjoin(file, str);
// 	}
// 	else
// 		file = str;
// 	stat(file, &items);
// 	flags->blocks = flags->blocks + items.st_blocks;
// 	user = *getpwuid(items.st_uid);
// 	if (ft_strlen(user.pw_name) > flags->uid)
// 		flags->uid = ft_strlen(user.pw_name);
// 	group = *getgrgid(items.st_gid);
// 	if (ft_strlen(group.gr_name) > flags->gid)
// 		flags->gid = ft_strlen(group.gr_name);
// 	if (ft_numullen(items.st_size) > flags->size)
// 		flags->size = ft_numullen(items.st_size);
// 	if (ft_numlen(items.st_nlink) > flags->nlinks)
// 		flags->nlinks = ft_numlen(items.st_nlink);
// 	if (ft_numlen(major(items.st_rdev)) > flags->major)
// 		flags->major = ft_numlen(major(items.st_rdev));
// 	if (ft_numlen(minor(items.st_rdev)) > flags->minor)
// 		flags->minor = ft_numlen(minor(items.st_rdev));
// }

/*
** I BELIEVE this was made to set my values in my struct to 0 when it needed to be
** resetted
*/
// void	reset_data(t_flags *flags)
// {
// 	flags->blocks = 0;
// 	flags->nlinks = 0;
// 	flags->uid = 0;
// 	flags->gid = 0;
// 	flags->size = 0;
// 	flags->device = 0;
// }

/*
** Function: check_and_set_flags
** This function checks the passed string to see if it contained any of the flags
** that is supported by ls. If so it will set the t_flags struct to 1 which will
** later be used to manipulate the printing output. Otherwise if it's not valid
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
		if (str[i] != 'r' && str[i] != 'a' && str[i] != '1'
			&& str[i] != 'l' && str[i] != 't' && str[i] != 'R')
		{
			ft_printf("ft_ls: illegal option -- '%c'\n", str[i]);
			ft_printf("Try 'ft_ls --help' for more information.\n");
			return (1);
		}
	}
	return (0);
}

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

void	set_list_elements(t_data *data, t_flags *flags)
{
	struct stat		items;
	struct passwd	user;
	struct group	group;

	lstat(data->file, &items);
	user = *getpwuid(items.st_uid);
	group = *getgrgid(items.st_gid);
	data->bits = perms(items.st_mode, flags);
	data->nlinks = items.st_nlink;
	data->uid = user.pw_name;
	data->gid = group.gr_name;
	data->size = items.st_size;
	data->major = major(items.st_rdev);
	data->minor = minor(items.st_rdev);
	data->mtime = ctime(&items.st_mtime);
}
/*
** Function: set_list_and_flags
** This function main goal is to generate a new t_data and set the
** new t_data->next to the data that was passed in. This way I can set
** a new information to the new data that was generated, allocate it memory
** and properly allow the initialize t_data to link all the new data together
** as a link list. In the end *data is set to the new data that was made.
** A simple breakdown, it also checks for any flags it may have to set those up.
** Goals: Will also set and parse all other information needed
*/
int		set_list_and_flags(char *str, t_flags *flags, t_data **data)
{
	t_data *new;

	if (str[0] == '0')
		if (check_and_set_flags(str, flags))
			return (0);
	if (str[0] != '-')
	{
		new = ft_memalloc(sizeof(t_data));
		new->next = *data;
		new->file = str;
		set_list_elements(new, flags);
	}
	*data = new;
	return (0);
}

/*
** Debugging function to make sure everything is being stored
** properly in the link list
*/
void	print_list(t_data *data)
{
	ft_printf("Printing data\n");
	while (data->next != NULL)
	{
		ft_printf("Current: %s, Next: %s\n", data->file, data->next->file);
		ft_printf("%s %i %s %s %llu %lu %lu %s\n", data->bits, data->nlinks, data->uid, data->gid, data->size, data->major, data->minor, data->mtime);
		data = data->next;
	}
}

/*
** Function: parse_input
** This function will generate two structs that will be used.
** First one is t_data, which is a linklist that will contain
** all the inputs being passed in.
** Second one is t_flags, which will contain all the flag flags
** that will allow the specialize printing in ft_ls
** If the ac == 1, meaning av[1] is NULL, it'll auto set the 
** file name (data->file) to "." which makes ./ft_ls behave
** the same as "./ft_ls ."
*/
int		parse_input(int ac, char **av)
{
	t_data	*data;
	t_flags *flags;
	int i;

	i = 0;
	data = ft_memalloc(sizeof(t_data));
	flags = ft_memalloc(sizeof(t_flags));
	if (ac == 1)
		set_list_and_flags(".", flags, &data);
	while (av[++i] && ac != 1)
		set_list_and_flags(av[i], flags, &data);
	print_list(data);
	print_list(data);
		// if (flags->exist == 0)
		// {
		// 	search[flags->exist] = ".";
		// 	flags->exist++;
		// }
		// sort_file_dir(search, flags->exist, flags);
	free(data);
	free(flags);
	return (0);
}