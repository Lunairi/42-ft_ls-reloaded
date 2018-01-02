/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

/*
** Function: swap_list
** A simple function that takes two link list, a variable
** for the iterative sort and sets it so that the function
** knows a sort occured. It simply moves the pointers around
** and returns the new swapped list.
*/

t_data	*swap_list(t_data *one, t_data *two, int *loop)
{
	one->next = two->next;
	two->next = one;
	*loop = 1;
	return (two);
}

/*
** Function: time_compare
** This is used to check the mtime between two elements in a linked
** list for time sort. It will also check nsec if time is the same.
** How it returns whether alphabetically or reversed is handled
** in the previous functions.
*/

int		time_compare(t_data *one, t_data *two)
{
	if (one->mtime > two->mtime)
		return (-1);
	if (one->mtime == two->mtime)
	{
		if (one->nsec > two->nsec)
			return (-1);
		else if (one->nsec == two->nsec)
			return (ft_strcmp(one->file, two->file));
	}
	return (1);
}
