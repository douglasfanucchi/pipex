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

static char	get_arg_delimiter(char *str_cmd)
{
	if (*str_cmd == 34)
		return ('"');
	if (*str_cmd == 39)
		return ('\'');
	return (' ');
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
	delimiter = get_arg_delimiter(str_cmd);
	str_end = str_cmd + 1;
	while (*str_end && *str_end != delimiter)
		str_end++;
	if (delimiter != ' ')
		offset = 1;
	args = get_args(str_end + offset, index + 1);
	args[index] = ft_substr(str_cmd, 0, str_end - str_cmd + offset);
	return (args);
}
