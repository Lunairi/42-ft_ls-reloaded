/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

/*
** Function: print_data_name
** This function continues off print_long and helps to print
** the date and any extra symbolic link information. It has to
** clear the buf each time to make sure that the data being printed
** for the symbolic link is accurate.
*/

void		print_date_name(t_data *data, t_flags *flags)
{
	char			buf[1024];
	ssize_t			len;
	char			*mtime;

	mtime = ctime(&data->mtime);
	flags->i = 3;
	while (++flags->i < 11)
		write(1, &mtime[flags->i], 1);
	if (time(NULL) - data->sec >= 15724800)
		print_xattr(flags, mtime);
	else
	{
		flags->i = 10;
		while (++flags->i < 16)
			write(1, &mtime[flags->i], 1);
	}
	ft_printf(" %s", data->file);
	if ((len = readlink(data->dir, buf, sizeof(buf))) != -1)
		ft_printf(" -> %s\n", buf);
	else
		ft_printf("\n");
	clear_buf(buf);
}

/* 
** Function: print_long
** This function is designed to help print all the elements that
** the data has when the l flag is called. It also uses the i
** variable to help with spacing to get an output similar to ls.
** This function continues into print_date_name.
*/
void	print_long(t_data *data, t_flags *flags)
{
	ft_printf("%s%c  ", perms(data->mode, flags), data->suffix);
	if ((flags->i = (flags->nlinks - ft_numlen(data->nlinks))) > 0)
		print_spacing(flags);
	ft_printf("%i ", data->nlinks);
	if ((flags->i = (flags->uid - ft_strlen(data->uid))) > 0)
		print_spacing(flags);
	ft_printf("%s  %s   ", data->uid, data->gid);
	if ((flags->i = (flags->gid - ft_strlen(data->gid))) > 0)
		print_spacing(flags);
	if (flags->device == 0)
	{
		if ((flags->i = (flags->size - ft_numullen(data->size))) > 0)
			print_spacing(flags);
		ft_printf("%llu ", data->size);
	}
	else
	{
		if ((flags->i = (flags->major - ft_numlen(major(data->device)))) > 0)
			print_spacing(flags);
		ft_printf("%lu, ", major(data->device));
		if ((flags->i = (flags->minor - ft_numlen(minor(data->device)))) > 0)
			print_spacing(flags);
		ft_printf("%lu  ", minor(data->device));
	}
	print_date_name(data, flags);
}

/*
** Function: print_list
** This function will help to print out the results
** based off what flags are necessary. All previous
** information has been setup prior so it's simply printing
** all the results.
*/

void	print_behavior(t_data *data, t_flags *flags)
{
	if(flags->a && !flags->l)
		ft_printf("%s\n", data->file);
	else if (flags->l && flags->a)
		print_long(data, flags);
	else if (flags->l && data->file[0] != '.')
		print_long(data, flags);
	else if (data->file && data->file[0] != '.')
	{
		ft_printf("%s\n", data->file);
	}
}

void	reset_flags(t_flags *flags)
{
	flags->nlinks = 0;
	flags->uid = 0;
	flags->gid = 0;
	flags->major = 0;
	flags->minor = 0;
	flags->size = 0;
	flags->device = 0;
	flags->blocks = 0;
}

// void	print_dir(t_data *data, t_flags *flags)
// {
// 	while (data != NULL && data->next != NULL)
// 	{
// 		if (S_ISDIR(data->mode))
// 		{
// 			if (flags->count++ != 0)
// 				ft_printf("\n");
// 			ft_printf("%s:\n", data->file);
// 			reset_flags(flags);
// 			parse_dir(data->file, flags);
// 		}
// 		data = data->next;
// 	}
// }


// int		parse_dir(char *dir, t_flags *flags)
// {
// 	t_data			*data;

// 	data = ft_memalloc(sizeof(t_data));
// 	set_one_arg(dir, 2, &data, flags);
// 	data = sort_link_list(data, flags, 1);
// 	if (flags->t == 1)
// 		data = time_sort_link_list(data, flags, 1);
// 	print_list(data, flags, 2);
// 	free(data);
// 	return (0);
// }

// int		parse_recur(char *dir, t_flags *flags)
// {
// 	t_data			*data;

// 	data = ft_memalloc(sizeof(t_data));
// 	set_one_arg(dir, 2, &data, flags);
// 	data = sort_link_list(data, flags, 1);
// 	if (flags->t == 1)
// 		data = time_sort_link_list(data, flags, 1);
// 	print_list(data, flags, 2);
// 	free(data);
// 	return (0);
// }

/*
** Function: grab_data_length
** This function is used to grab the length of each information stored
** to help with formatting when time comes for printing.
*/

void	grab_dir_data_length(t_data *data, t_flags *flags)
{
	while(data != NULL && data->next != NULL)
	{
		if ((!flags->a && data->file[0] != '.') || (flags->a))
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
		data = data->next;
	}
}


void	print_dir(t_data *data, t_flags *flags)
{
	t_data *dir;

	while (data != NULL && data->next != NULL)
	{
		if (S_ISDIR(data->mode))
		{
			reset_flags(flags);
			if (flags->count++ != 0)
				ft_printf("\n");
			ft_printf("%s:\n", data->file);
			if (data->d != NULL)
			{
				dir = data->d;
				grab_dir_data_length(dir, flags);
				ft_printf("total %lli\n", flags->blocks);
				while (dir != NULL && dir->next != NULL)
				{
					if (ft_strcmp(dir->file, "") && ft_strcmp(dir->file, ""))
						print_behavior(dir, flags);
					dir = dir->next;
				}
				free_struct(&dir);
			}
		}
		data = data->next;
	}
}

void	print_recur(t_data *data, t_flags *flags)
{
	t_data *dir;
	t_data *re;
	t_data *con;

	while (data != NULL && data->next != NULL)
	{
		if (S_ISDIR(data->mode))
		{
			reset_flags(flags);
			if (flags->count++ != 0 && data->d != NULL)
				ft_printf("\n");
			if (data->d != NULL)
			{
				dir = data->d;
				re = data->d;
				grab_dir_data_length(dir, flags);
				ft_printf("%s:\n", data->file);
				ft_printf("total %lli\n", flags->blocks);
				while (dir != NULL && dir->next != NULL)
				{
					if (ft_strcmp(dir->file, ""))
						print_behavior(dir, flags);
					dir = dir->next;
				}
				while (re != NULL && re->next != NULL)
				{
					con = ft_memalloc(sizeof(t_data));
					if (S_ISDIR(re->mode) && ft_strcmp(re->file, ".") && ft_strcmp(re->file, "..")
						&& ft_strcmp(re->file, ""))
					{
						branch_dir_content(re->dir, &con, flags);
						print_recur(con, flags);
					}
					free(con);
					re = re->next;
				}
			}
		}
		data = data->next;
	}
}




void	print_list(t_data *data, t_flags *flags)
{
	t_data *print;

	print = data;
	while (flags->ac <= 2 && print->file != NULL && print->next != NULL)
	{
		print_behavior(print, flags);
		print = print->next;
	}
	while (flags->ac > 2 && print->file != NULL && print->next != NULL)
	{
		if (!S_ISDIR(print->mode))
		{
			flags->count++;
			print_behavior(print, flags);
		}
		print = print->next;
	}
	if (flags->ac > 2 && !flags->re)
		print_dir(data, flags);
	else if (flags->re)
		print_recur(data, flags);
}
