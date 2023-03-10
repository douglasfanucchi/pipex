/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:18:11 by dfanucch          #+#    #+#             */
/*   Updated: 2022/12/27 14:18:12 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static char	*get_pathname(char *bin, char **paths)
{
	char	*pathname;
	char	*slash_bin;

	if (*bin == '/' || ft_strncmp("./", bin, 2) == 0
		|| ft_strncmp("../", bin, 3) == 0 || ft_strncmp(bin, "~/", 2) == 0)
		return (ft_strdup(bin));
	slash_bin = ft_strjoin("/", bin);
	while (*paths)
	{
		pathname = ft_strjoin(*paths, slash_bin);
		if (access(pathname, F_OK) == 0)
		{
			free(slash_bin);
			return (pathname);
		}
		free(pathname);
		paths++;
	}
	free(slash_bin);
	return (ft_strdup(""));
}

static char	*get_filename(char *str_cmd)
{
	char	*str_end;

	if (!str_cmd)
		return (ft_strdup(""));
	while (ft_isspace(*str_cmd))
		str_cmd++;
	str_end = str_cmd;
	while (*str_end && !ft_isspace(*str_end))
		str_end++;
	return (ft_substr(str_cmd, 0, str_end - str_cmd));
}

void	del_command(void *cmd)
{
	char		**argv;
	t_command	*command;

	command = cmd;
	argv = command->argv;
	free(command->filename);
	free(command->pathname);
	while (*argv)
	{
		free(*argv);
		argv++;
	}
	free(command->argv);
	free(command);
}

t_command	*new_command(char *str_cmd, char **envp, char **paths)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	command->filename = get_filename(str_cmd);
	command->pathname = get_pathname(command->filename, paths);
	command->argv = get_command_args(str_cmd + ft_strlen(command->filename), 1);
	command->argv[0] = ft_strdup(command->filename);
	command->input_fd = -1;
	command->output_fd = -1;
	command->envp = envp;
	command->bash_status = 1;
	command->pid = 0;
	command->pipe[0] = 0;
	command->pipe[1] = 0;
	return (command);
}
