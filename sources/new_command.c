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
	return (NULL);
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

static char	**get_args(char *str_cmd, int index)
{
	char	**args;
	char	delimiter;
	char	*str_end;
	int		offset;

	offset = 0;
	while (ft_isspace(*str_cmd))
		str_cmd++;
	if (!*str_cmd)
	{
		args = malloc(sizeof(char **) * (index + 1));
		args[index] = NULL;
		return (args);
	}
	delimiter = ' ';
	if (*str_cmd == '\'' || *str_cmd == '"')
		delimiter = *str_cmd;
	str_end = str_cmd + 1;
	while (*str_end && *str_end != delimiter)
		str_end++;
	if (delimiter != ' ')
		offset = 1;
	args = get_args(str_end + offset, index + 1);
	args[index] = ft_substr(str_cmd, 0, str_end - str_cmd + offset);
	return (args);
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
	close(command->input_fd);
	close(command->output_fd);
}

t_command	*new_command(char *str_cmd, char **envp, char **paths)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	command->filename = get_filename(str_cmd);
	command->pathname = get_pathname(command->filename, paths);
	command->argv = get_args(str_cmd + ft_strlen(command->filename), 1);
	command->argv[0] = ft_strdup(command->filename);
	command->envp = envp;
	return (command);
}
