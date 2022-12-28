/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 22:53:45 by dfanucch          #+#    #+#             */
/*   Updated: 2022/12/26 22:53:45 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void	set_commands_file_descriptors(t_list **cmd_list, int *files)
{
	t_command	*command;

	command = (*cmd_list)->content;
	command->input_fd = files[0];
	command = ft_lstlast(*cmd_list)->content;
	command->output_fd = files[1];
}

int	exec_cmd(t_list *node)
{
	t_command	*command;
	int			fd[2];
	pid_t		pid;

	pipe(fd);
	command = node->content;
	if (!command->pathname)
	{
		ft_printf("%s: command not found\n", command->filename);
		return (127);
	}
	if (node->next)
	{
		((t_command *)node->next->content)->input_fd = fd[0];
		command->output_fd = fd[1];
	}
	pid = fork();
	if (!pid)
	{
		dup2(command->input_fd, 0);
		dup2(command->output_fd, 1);
		execve(command->pathname, command->argv, command->envp);
	}
	waitpid(pid, NULL, 0);
	close(fd[1]);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_list		**cmd_list;
	int			files[2];
	t_list		*node;
	int			status;

	if (!validate_args(argc))
	{
		ft_printf("Invalid parameters.\n");
		return (1);
	}
	open_files(files, argv + 1, argc - 1);
	cmd_list = get_commands(argv, envp);
	set_commands_file_descriptors(cmd_list, files);
	node = *cmd_list;
	while (node)
	{
		status = exec_cmd(node);
		if (status)
		{
			ft_lstclear(cmd_list, del_command);
			exit(status);
		}
		node = node->next;
	}
	ft_lstclear(cmd_list, del_command);
}
