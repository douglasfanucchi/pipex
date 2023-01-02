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

static int	file_exists(char *file)
{
	return (access(file, F_OK) == 0);
}

static int	has_permission(char *file, int mode)
{
	return (access(file, mode) == 0);
}

void	open_files(int *files, char **argv, int args)
{
	if (!file_exists(argv[0]))
		ft_printf("%s: No such file or directory\n", argv[0]);
	else if (!has_permission(argv[0], R_OK))
		ft_printf("%s: Permission denied\n", argv[0]);
	files[0] = open(argv[0], O_RDONLY);
	files[1] = open(argv[args - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (files[1] == -1)
		ft_printf("%s: Permission denied\n", argv[args - 1]);
}
