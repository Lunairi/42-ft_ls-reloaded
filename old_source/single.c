/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

int		ls_single(char *str, t_flags *toggle)
{
	struct dirent	*d;
	DIR				*dir;
	char			**list;
	int				i;
	int				item;

	i = 0;
	if (!(item = item_amount(str, toggle)))
		return (0);
	list = (char**)ft_memalloc(sizeof(char*) * 999999);
	dir = opendir(str);
	while ((d = readdir(dir)))
	{
		list[i] = d->d_name;
		i++;
	}
	if (toggle->t == 1)
		time_sort_recursive(list, i, toggle, str);
	else
		sort_recursive(list, i, toggle, str);
	closedir(dir);
	free(list);
	return (0);
}
