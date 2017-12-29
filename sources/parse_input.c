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

int		check_flags(char *str, t_flags *flags)
{
	int i;

	i = 0;
	while (str[++i] != '\0')
	{
		str[i] == 'r' ? flags->r = 1 : 0;
		str[i] == 'a' ? flags->a = 1 : 0;
		str[i] == 'l' ? flags->l = 1 : 0;
		str[i] == 't' ? flags->t = 1 : 0;
		str[i] == 'R' ? flags->re = 1 : 0;
		if (str[i] != 'r' && str[i] != 'a' && str[i] != '1'
			&& str[i] != 'l' && str[i] != 't' && str[i] != 'R')
		{
			ft_printf("ft_ls: illegal option -- '%c'\n", str[i]);
			ft_printf("Try 'ft_ls --help' for more information.\n");
			return (1);
		}
	}
	return (0);
}

/*
** Function: set_list_and_flags
** This function main goal is to generate a new t_data and set the
** new t_data->next to the data that was passed in. This way I can set
** a new information to the new data that was generated, allocate it memory
** and properly allow the initialize t_data to link all the new data together
** as a link list. In the end *data is set to the new data that was made.
** A simple breakdown, it also checks for any flags it may have to set those up.
** Goals: Will also set and parse all other information needed
*/
int		set_list_and_flags(char *str, t_flags *flags, t_data **data)
{
	t_data *new;

	if (str[0] == '0')
		if (check_flags(str, flags))
			return (0);
	if (str[0] != '-')
	{
		new = ft_memalloc(sizeof(t_data));
		new->next = *data;
		new->file = str;
		ft_printf("Data inserted %s\n", new->file);
	}
	*data = new;
	return (0);
}

/*
** Debugging function to make sure everything is being stored
** properly in the link list
*/
void	print_list(t_data *data)
{
	ft_printf("Printing data\n");
	while (data->next != NULL)
	{
		ft_printf("%s, next %s\n", data->file, data->next->file);
		data = data->next;
	}
}

/*
** Function: parse_input
** This function will generate two structs that will be used.
** First one is t_data, which is a linklist that will contain
** all the inputs being passed in.
** Second one is t_flags, which will contain all the flag toggle
** that will allow the specialize printing in ft_ls
** If the ac == 1, meaning av[1] is NULL, it'll auto set the 
** file name (data->file) to "." which makes ./ft_ls behave
** the same as "./ft_ls ."
*/
int		parse_input(int ac, char **av)
{
	t_data	*data;
	t_flags *flags;
	int i;

	i = 0;
	data = ft_memalloc(sizeof(t_data));
	flags = ft_memalloc(sizeof(t_flags));
	if (ac == 1)
		set_list_and_flags(".", flags, &data);
	while (av[++i] && ac != 1)
		set_list_and_flags(av[i], flags, &data);
	print_list(data);
		// if (toggle->exist == 0)
		// {
		// 	search[toggle->exist] = ".";
		// 	toggle->exist++;
		// }
		// sort_file_dir(search, toggle->exist, toggle);
	free(data);
	free(flags);
	return (0);
}