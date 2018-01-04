/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

/*
** Function: print_spacing
** This was the hardest function I've ever written. Printing spaces is hard.
*/

void	print_spacing(t_flags *flags)
{
	while (flags->i-- > 0)
		ft_printf(" ");
}

/*
** Function: print_xattr
** This function is designed to help print the extended attributes
** and provide additional padding to it as well so it aligns with ls.
*/

void	print_xattr(t_flags *flags, char *mtime)
{
	flags->i = 19;
	write(1, " ", 1);
	while (++flags->i < 24)
		write(1, &mtime[flags->i], 1);
}

/*
** Function: clear_buf
** Clears the buf from the function print_data_name
** to help clear buf for symbolic link info.
*/

void	clear_buf(char *buf)
{
	int i;

	i = ft_strlen(buf);
	i--;
	while (i >= 0)
	{
		buf[i] = '\0';
		i--;
	}
}

/*
** Function: free_helper
** This function helps to free the child of each directory if data->d exist.
*/

void	free_helper(t_data *data)
{
	t_data	*tmp;

	while (data && data->next)
	{
		tmp = data->next;
		if (data->d)
		{
			free_helper(data->d);
			free(data->d);
			data->d = NULL;
		}
		if (data->file)
		{
			free(data->file);
			data->file = NULL;
		}
		if (data->dir)
		{
			free(data->dir);
			data->dir = NULL;
		}
		data = tmp;
	}
}

/*
** Function: free_struct
** This function is used to help free elements in the struct and if
** there is any data->d for child content it will be sent to the helper
** recursively to remove the content inside that link list.
*/

void	free_struct(t_data **data)
{
	t_data	*tmp;

	while (data && *data)
	{
		tmp = (*data)->next;
		if ((*data)->d)
		{
			free_helper((*data)->d);
			(*data)->d = NULL;
		}
		if ((*data)->file)
		{
			free((*data)->file);
			(*data)->file = NULL;
		}
		if ((*data)->dir)
		{
			free((*data)->dir);
			(*data)->dir = NULL;
		}
		free(*data);
		*data = tmp;
	}
}
