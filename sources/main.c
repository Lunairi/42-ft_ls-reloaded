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

int		main(int ac, char **av)
{
	if(ac != 1)
		if (!(ft_strcmp(av[1], "--help")))
			return (help_ls());
	parse_input(ac, av, 0);
	return (0);
}
