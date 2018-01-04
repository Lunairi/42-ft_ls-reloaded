/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/28 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftls.h"

int		help_ls(void)
{
	ft_printf("Usage: ft_ls [OPTION]... [FILE]...\n");
	ft_printf("List information about the FILES \
(the current directory by default).\n");
	ft_printf("Mandatory arguments to long options are \
mandatory for short options too.\n");
	ft_printf("-a,             do not ignore entries starting with .\n");
	ft_printf("-l              use a long listing format\n");
	ft_printf("-r,             reverse order while sorting\n");
	ft_printf("-R,             list subdirectories recursively\n");
	ft_printf("-t              sort by modification time, newest first\n");
	ft_printf("-1              list one file per line\n");
	ft_printf("--help          display this help and exit\n");
	return (0);
}

/*
** Function: parse_input
** This function will generate two structs that will be used.
** First one is t_data, which is a linklist that will contain
** all the inputs being passed in.
** Second one is t_flags, which will contain all the flag flags
** that will allow the specialize printing in ft_ls
** If the ac == 1, meaning av[1] is NULL, it'll auto set the
** file name (data->file) to "." which makes ./ft_ls behave
** the same as "./ft_ls ."
*/

int		parse_input(int ac, char **av, int i)
{
	t_data			*data;
	t_flags			*flags;

	data = ft_memalloc(sizeof(t_data));
	flags = ft_memalloc(sizeof(t_flags));
	flags->ac = ac;
	if (ac <= 2)
		set_one_arg(av[1], ac, &data, flags);
	if (flags->re)
		branch_dir_content(".", &data, flags);
	while (av[++i] && ac > 2)
		branch_dir_content(av[i], &data, flags);
	data = sort_link_list(data, flags, 1);
	data = sort_link_list(data, flags, 1);
	if (flags->t == 1)
		data = time_sort_link_list(data, flags, 1);
	if (flags->error != 1)
		print_list(data, flags);
	free_struct(&data);
	free(flags);
	return (0);
}

/*
** Function: main
** This takes the input and helps to send it properly. The first one
** detects --help, the rest is fed into parse_input
*/

int		main(int ac, char **av)
{
	if (ac != 1)
		if (!(ft_strcmp(av[1], "--help")))
			return (help_ls());
	parse_input(ac, av, 0);
	return (0);
}
