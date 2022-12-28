/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:12:34 by dfanucch          #+#    #+#             */
/*   Updated: 2022/12/28 14:12:36 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	check_exists(char *file)
{
	if (access(file, F_OK) == -1)
	{
		ft_printf("%s: No such file or directory\n", file);
		exit(1);
	}
}

static void	check_permission(char *file, int mode)
{
	if (access(file, mode) == -1)
	{
		ft_printf("%s: Permission denied\n", file);
		exit(1);
	}
}

void	open_files(int *files, char **argv, int args)
{
	check_exists(files[0]);
	check_permission(files[0], R_OK);
	files[0] = open(argv[0], O_RDONLY);
	files[1] = open(argv[args - 1], O_WRONLY | O_CREAT);
	if (files[1] == -1)
	{
		close(files[0]);
		ft_printf("%s: Permission denied\n", argv[args - 1]);
		exit(1);
	}
}
