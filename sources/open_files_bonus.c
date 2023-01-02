/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 03:44:52 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/02 18:26:50 by dfanucch         ###   ########.fr       */
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

static void	create_here_doc(char *limiter)
{
	char	*next_line;
	int		fd;

	fd = open(".tmp_here_doc", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf(".tmp_here_doc: Permission denied\n");
		return ;
	}
	write(1, "heredoc> ", 9);
	next_line = get_next_line(0);
	while (next_line)
	{
		if (ft_strncmp(next_line, limiter, ft_strlen(next_line)) - '\n' == 0)
		{
			free(next_line);
			break ;
		}
		write(fd, next_line, ft_strlen(next_line));
		free(next_line);
		write(1, "heredoc> ", 9);
		next_line = get_next_line(0);
	}
	close(fd);
}

void	open_files(int *files, char **argv, int args)
{
	char	*read_file;
	int		output_flags;

	output_flags = O_CREAT | O_WRONLY | O_TRUNC;
	read_file = argv[0];
	if (ft_strncmp(read_file, "here_doc", ft_strlen(read_file)) == 0)
	{
		output_flags = O_CREAT | O_WRONLY | O_APPEND;
		read_file = ".tmp_here_doc";
		create_here_doc(argv[1]);
	}
	if (!file_exists(read_file))
		ft_printf("%s: No such file or directory\n", read_file);
	else if (!has_permission(read_file, R_OK))
		ft_printf("%s: Permission denied\n", read_file);
	files[0] = open(read_file, O_RDONLY);
	files[1] = open(argv[args - 1], output_flags, 0644);
	if (files[1] == -1)
		ft_printf("%s: Permission denied\n", argv[args - 1]);
}
