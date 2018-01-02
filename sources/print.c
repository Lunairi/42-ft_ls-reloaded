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
	if ((len = readlink(data->dir, buf, sizeof(buf) - 1)) != -1)
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
	else if (data->file[0] != '.')
		ft_printf("%s\n", data->file);
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
}

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


void	print_recur(t_data *data, t_flags *flags)
{
	ft_printf("FUCK %s\n", data->dir);
	while (data != NULL && data->next != NULL)
	{
		if (S_ISDIR(data->mode))
		{ft_printf("FUCK");
			if (flags->count++ != 0)
				ft_printf("\n");
			ft_printf("%s:\n", data->file);
			reset_flags(flags);
			parse_dir(data->file, flags);
		}
		data = data->next;
	}
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

void	print_dir(t_data *data, t_flags *flags)
{
	while (data != NULL && data->next != NULL)
	{
		// if (data->d != NULL)
			ft_printf("DIRECTORY %s\n", data->file);
		if (S_ISDIR(data->mode))
		{
			if (flags->count++ != 0)
				ft_printf("\n");
			ft_printf("%s:\n", data->file);
			// ft_printf("FUCK %s %s\n", data->file, data->d->file);
			// if (data->d != NULL)
			// {
			// 	data = sort_link_list(data, flags, 1);
			// 		if (flags->t == 1)
			// 	data = time_sort_link_list(data, flags, 1);
			// }
			if (data->d != NULL)
			{
				data = data->d;
				ft_printf("NEXT ITEM %s\n", data->file);
			}
			while (data != NULL && data->next != NULL)
			{
				ft_printf("PENIS%s FUCK %s\n", data->file, data->next->file);
				print_behavior(data, flags);
				data = data->next;
			}
			// reset_flags(flags);
			// parse_dir(data->file, flags);
		}
		data = data->next;
	}
}


void	print_list(t_data *data, t_flags *flags, int ac)
{
	t_data *print;

	print = data;
	while (ac <= 2 && print != NULL && print->next != NULL && !flags->re)
	{
		print_behavior(print, flags);
		print = print->next;
	}
	while (ac > 2 && print != NULL && print->next != NULL && flags->print++ == 0)
	{
		if (!S_ISDIR(print->mode))
			print_behavior(print, flags);
		print = print->next;
	}
	if (ac > 2)
		print_dir(data, flags);
	// else if (flags->re)
	// 	print_recur(data, flags);
}
