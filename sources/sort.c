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
** Function: time_sort_link_list
** This function is just like sort_link_list but instead this
** sorts the link list one more time based off time. It will
** check again for reverse flag, but otherwise displays time
** properly.
*/

t_data	*time_sort_link_list(t_data *data, t_flags *flags, int loop)
{
	t_data *one;
	t_data *two;
	t_data *new;

	new = ft_memalloc(sizeof(t_data));
	new->next = data;
	while (loop && data->file != NULL && data->next->file != NULL)
	{
		loop = 0;
		one = new;
		two = new->next;
		while (two->file != NULL && two->next->file != NULL)
		{
			if ((time_compare(two, two->next) > 0 && flags->r == 0)
			|| (time_compare(two->next, two) > 0 && flags->r == 1))
				one->next = swap_list(two, two->next, &loop);
			one = two;
			if (two->next->file != NULL)
				two = two->next;
		}
	}
	two = new->next;
	free(new);
	return (two);
}

/*
** Function: sort_link_list
** This function is a simple iterative bubble sort. It
** makes three points of data, one that is a copy of data
** and the other two used to move around pointers and nodes.
** It determines and behaves based off ->file which is the
** names of all of the elements. It will later go into
** swap_list which will swap the elements. In the end it
** will free new and return back the newly sorted linked list.
** This will also sort reversed if the flag->r is toggled to 1,
** if not it will do regular sorting.
*/

t_data	*sort_link_list(t_data *data, t_flags *flags, int loop)
{
	t_data *one;
	t_data *two;
	t_data *new;

	new = ft_memalloc(sizeof(t_data));
	new->next = data;
	while (loop && data->file != NULL && data->next->file != NULL)
	{
		loop = 0;
		one = new;
		two = new->next;
		while (two->file != NULL && two->next->file != NULL)
		{
			if ((ft_strcmp(two->file, two->next->file) > 0 && flags->r == 0)
			|| (ft_strcmp(two->next->file, two->file) > 0 && flags->r == 1))
				one->next = swap_list(two, two->next, &loop);
			one = two;
			if (two->next->file != NULL)
				two = two->next;
		}
	}
	two = new->next;
	free(new);
	return (two);
}
