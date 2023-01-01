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

void	set_commands_file_descriptors(t_list **cmd_list, int *files);
int		exec_cmd(t_command *cmd, t_command *next_cmd);
void	run_commands(t_list **commands);
void	set_bash_status(t_list **commands, t_command *last_cmd);

int	main(int argc, char **argv, char **envp)
{
	t_list		**cmd_list;
	int			files[2];
	t_command	*last_command;
	int			status;

	status = 0;
	if (!validate_args(argc))
	{
		ft_printf("Invalid parameters.\n");
		return (1);
	}
	open_files(files, argv + 1, argc - 1);
	cmd_list = get_commands(argv, envp);
	set_commands_file_descriptors(cmd_list, files);
	run_commands(cmd_list);
	last_command = ft_lstlast(*cmd_list)->content;
	status = last_command->bash_status;
	close_files(files);
	ft_lstclear(cmd_list, del_command);
	return (status);
}

void	set_commands_file_descriptors(t_list **cmd_list, int *files)
{
	t_command	*command;

	command = (*cmd_list)->content;
	command->input_fd = files[0];
	command = ft_lstlast(*cmd_list)->content;
	command->output_fd = files[1];
}

int	exec_cmd(t_command *cmd, t_command *next_cmd)
{
	pipe(cmd->pipe);
	if (!*cmd->pathname)
	{
		ft_printf("%s: command not found\n", cmd->filename);
		cmd->bash_status = 127;
	}
	if (next_cmd)
	{
		cmd->output_fd = cmd->pipe[1];
		next_cmd->input_fd = cmd->pipe[0];
	}
	cmd->pid = fork();
	if (!cmd->pid)
	{
		dup2(cmd->input_fd, 0);
		dup2(cmd->output_fd, 1);
		close(cmd->pipe[0]);
		close(cmd->pipe[1]);
		if (cmd->input_fd != -1 && cmd->output_fd != -1)
			execve(cmd->pathname, cmd->argv, cmd->envp);
		return (1);
	}
	close(cmd->pipe[1]);
	return (0);
}

void	run_commands(t_list **commands)
{
	t_list		*node;
	t_command	*prev_cmd;
	int			exec_failed;
	t_command	*last_cmd;

	prev_cmd = NULL;
	node = *commands;
	while (node)
	{
		if (node->next)
			exec_failed = exec_cmd(node->content, node->next->content);
		else
			exec_failed = exec_cmd(node->content, NULL);
		if (prev_cmd)
			close(prev_cmd->pipe[0]);
		if (exec_failed)
			break ;
		prev_cmd = node->content;
		node = node->next;
	}
	last_cmd = ft_lstlast(*commands)->content;
	set_bash_status(commands, last_cmd);
	if (last_cmd->pipe[0])
		close(last_cmd->pipe[0]);
}

void	set_bash_status(t_list **commands, t_command *last_cmd)
{
	int		status;
	t_list	*node;

	status = -1;
	waitpid(last_cmd->pid, &status, 0);
	if (WIFEXITED(status))
		last_cmd->bash_status = WEXITSTATUS(status);
	node = *commands;
	while (node)
	{
		if (node->next)
			wait(NULL);
		node = node->next;
	}
}
