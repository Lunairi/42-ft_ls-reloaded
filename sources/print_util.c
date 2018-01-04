/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

/*
** Function: grab_data_length
** This function is used to grab the length of each information stored
** to help with formatting when time comes for printing.
*/

void	grab_dir_data_length(t_data *data, t_flags *flags)
{
	while (data != NULL && data->next != NULL)
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

/*
** Function: print_data_name
** This function continues off print_long and helps to print
** the date and any extra symbolic link information. It has to
** clear the buf each time to make sure that the data being printed
** for the symbolic link is accurate.
*/

void	print_date_name(t_data *data, t_flags *flags)
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
	if (buf[0] != '\0')
		clear_buf(buf);
}

/*
** Function: reset_flags
** This resets the flags between each new directory so the proper
** spacing can be printed for each directory content.
*/

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

/*
** Function: print_behavior
** This function will help to print out the results
** based off what flags are necessary. All previous
** information has been setup prior so it's simply printing
** all the results.
*/

void	print_behavior(t_data *data, t_flags *flags)
{
	if (flags->a && !flags->l)
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
