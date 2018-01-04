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
** Function: set_list_elements
** This function is to grab all the elements of the specific item that
** is being passed into here. It will be able to record the mode (type),
** the bits, uid, gid, bits, nlink, size, major/minor devices and mtime.
** All of this is later to be used to do sorting and help with flags.
** It also will not store any data if set list elements finds that the
** arguement passed is invalid.
** like -r -t -a etc.
*/

int		set_list_elements(char *str, char *dir, t_data *data, t_flags *flags)
{
	struct stat		items;
	struct passwd	user;
	struct group	group;

	if (lstat(dir, &items))
	{
		ft_printf("ft_ls %s: %s\n", str, strerror(errno));
		return (0);
	}
	data->file = ft_strdup(str);
	data->blocks = items.st_blocks;
	data->mode = items.st_mode;
	user = *getpwuid(items.st_uid);
	group = *getgrgid(items.st_gid);
	data->bits = perms(items.st_mode, flags);
	data->nlinks = items.st_nlink;
	data->uid = user.pw_name;
	data->gid = group.gr_name;
	data->size = items.st_size;
	data->device = items.st_rdev;
	data->mtime = items.st_mtime;
	data->nsec = items.st_mtimespec.tv_nsec;
	data->sec = items.st_mtimespec.tv_sec;
	set_more_list_elements(str, dir, data, flags);
	return (1);
}

/*
** Function: set_list_and_flags
** This function main goal is to generate a new t_data and set the
** new t_data->next to the data that was passed in. This way I can set
** a new information to the new data that was generated, allocate it memory
** and properly allow the initialize t_data to link all the new data together
** as a link list. In the end *data is set to the new data that was made.
** A simple breakdown, it also checks for any flags it may have to set those up.
** It will only take the flags before file args, endflag will be marked to 1
** when there is a break in flags.
** Goals: Will also set and parse all other information needed
*/

void	free_stuff(char *dir, t_data *new)
{
	free(dir);
	free(new);
}

int		set_list_and_flags(char *str, char *dir, t_flags *flags, t_data **data)
{
	t_data	*new;

	if (str[0] == '-' && str[1] != '\0' && flags->endflag != 1)
	{
		if (check_and_set_flags(str, flags))
			return (0);
	}
	else
	{
		flags->endflag = 1;
		new = ft_memalloc(sizeof(t_data));
		if (dir != NULL)
			dir = ft_strjoin(dir, str);
		else
			dir = ft_strdup(str);
		if (set_list_elements(str, dir, new, flags))
		{
			new->dir = dir;
			new->next = *data;
			*data = new;
		}
		else
		{
			free_stuff(dir, new);
			// free(dir);
			// free(new);
		}
	}
	return (1);
}

/*
** Function: get_dir_content
** This function is designed to pull all content of the dir and store
** it into a new linked list. Once it's done it'll be set back to the
** previous function where it'll be sorted and linked to the original
** link list.
*/

int		get_dir_content(char *str, t_data **data, t_flags *flags)
{
	DIR				*dirt;
	struct dirent	*d;
	char			*cur;

	if (!(dirt = opendir(str)))
		return (0);
	while ((d = readdir(dirt)))
	{
		cur = ft_strjoin(str, "/");
		set_list_and_flags(d->d_name, cur, flags, data);
		free(cur);
	}
	closedir(dirt);
	return (1);
}

/*
** Function: branch_dir_content
** This function checks the input from multiple arguements and sees if
** a directory or command. If it's a command it'll parse it and set
** the elements inside the link list.
*/

void	branch_dir_content(char *av, t_data **data, t_flags *flags)
{
	t_data *new;

	if (!(set_list_and_flags(av, NULL, flags, data)))
		return ;
	if (S_ISDIR((*data)->mode))
	{
		new = ft_memalloc(sizeof(t_data));
		if (!(get_dir_content(av, &new, flags)))
		{
			free(new);
			return ;
		}
		if (new)
		{
			new = sort_link_list(new, flags, 1);
			if (flags->t == 1)
				new = time_sort_link_list(new, flags, 1);
			(*data)->d = new;
		}
	}
	else
		(*data)->d = NULL;
}

/*
** Function: set_one_arg
** This function will handle zero or one arguments passed to ft_ls
** due to how they behave different than having multiple arguments.
*/

void	set_one_arg(char *av, int ac, t_data **data, t_flags *flags)
{
	DIR				*dirt;
	struct dirent	*d;
	char			*str;

	if (ac == 1)
		av = ".";
	str = av;
	if (str[0] == '-' && str[1] != '\0')
	{
		check_and_set_flags(str, flags);
		set_str_av(&av, &str);
	}
	if (!(dirt = opendir(str)))
	{
		set_list_and_flags(str, NULL, flags, data);
		return ;
	}
	while ((d = readdir(dirt)))
	{
		str = ft_strjoin(str, "/");
		set_list_and_flags(d->d_name, str, flags, data);
		free(str);
		str = av;
	}
	closedir(dirt);
}
