/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

/*
** Function: free_stuff
** Continuation of set_list_and_flags in parse_input.c due to norminette
*/

void	free_stuff(char *dir, t_data *new)
{
	free(dir);
	free(new);
}

/*
** Function: print_recur_dir
** Continuation of print_recur in print.c due to norminette
*/

void	print_recur_dir(t_data *data, t_flags *flags, t_data *dir)
{
	grab_dir_data_length(dir, flags);
	ft_printf("%s:\n", data->file);
	if (flags->blocks && flags->l)
		ft_printf("total %lli\n", flags->blocks);
}

/*
** Function: reset_and_check_dir
** Continuation of print_dir in print.c due to norminette
*/

void	reset_and_check_dir(t_flags *flags)
{
	reset_flags(flags);
	if (flags->count++ != 0)
		ft_printf("\n");
}

/*
** Function: set_more_list_elements
** Continuation of set_list_elements in parse_input.c due to norminette
*/

void	set_more_list_elements(char *str, char *dir,
			t_data *data, t_flags *flags)
{
	suffix(dir, data);
	grab_data_length(data, flags);
}

/*
** Function: set_str_av
** Continuation of set_ong_arg in parse_input.c due to norminette
*/

void	set_str_av(char **av, char **str)
{
	*str = ".";
	*av = ".";
}
