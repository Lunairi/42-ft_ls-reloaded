/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

/*
** Function: print_long
** This function is designed to help print all the elements that
** the data has when the l flag is called. It also uses the i
** variable to help with spacing to get an output similar to ls.
** This function continues into print_date_name.
*/

void	print_long(t_data *data, t_flags *flags)
{
	ft_printf("%s%c ", perms(data->mode, flags), data->suffix);
	if ((flags->i = (flags->nlinks - ft_numlen(data->nlinks))) > 0)
		print_spacing(flags);
	ft_printf("%i ", data->nlinks);
	if ((flags->i = (flags->uid - ft_strlen(data->uid))) > 0)
		print_spacing(flags);
	ft_printf("%s  %s  ", data->uid, data->gid);
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
** Function: print_dir
** This function helps to print out the content of directories.
*/

void	print_dir(t_data *data, t_flags *flags)
{
	t_data *dir;

	while (data != NULL && data->next != NULL)
	{
		if (S_ISDIR(data->mode))
		{
			reset_and_check_dir(flags);
			if (flags->ac != 3)
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
			}
		}
		data = data->next;
	}
}

/*
** Function: print_recur
** This function helps with recursive printing, it creates
** a couple of copy of t_data so that it can print directory
** and allow recursive behavior with more directories.
*/

void	print_recur_process(t_data *data, t_flags *flags)
{
	t_data *dir;
	t_data *re;
	t_data *con;

	dir = data->d;
	re = data->d;
	print_recur_dir(data, flags, dir);
	while (dir != NULL && dir->next != NULL)
	{
		if (ft_strcmp(dir->file, ""))
			print_behavior(dir, flags);
		dir = dir->next;
	}
	while (re != NULL && re->next != NULL)
	{
		con = ft_memalloc(sizeof(t_data));
		if (S_ISDIR(re->mode) && ft_strcmp(re->file, ".")
			&& ft_strcmp(re->file, "..") && ft_strcmp(re->file, ""))
		{
			branch_dir_content(re->dir, &con, flags);
			print_recur(con, flags);
		}
		free_struct(&con);
		re = re->next;
	}
}

void	print_recur(t_data *data, t_flags *flags)
{
	t_data			*next;

	next = 0;
	while (data != NULL && data->next != NULL)
	{
		if (S_ISDIR(data->mode))
		{
			reset_flags(flags);
			if (flags->count++ != 0 && data->d != NULL)
				ft_printf("\n");
			if (data->d != NULL)
				print_recur_process(data, flags);
		}
		next = data->next;
		data = next;
	}
}

/*
** Function: print_list
** This function helps to print out the output for ls. It's designed to
** first print out all non directory items first before printing dir
** and their contents.
*/

void	print_list(t_data *data, t_flags *flags)
{
	t_data *print;

	print = data;
	if (flags->l && flags->ac <= 2)
		ft_printf("total %lli\n", flags->blocks);
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
