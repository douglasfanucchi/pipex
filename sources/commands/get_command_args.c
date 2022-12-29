/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 04:48:53 by dfanucch          #+#    #+#             */
/*   Updated: 2022/12/29 04:48:53 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static char	**malloc_args(int index)
{
	char	**args;

	args = malloc(sizeof(char **) * (index + 1));
	if (!args)
		return (NULL);
	args[index] = NULL;
	return (args);
}

char	**get_command_args(char *str_cmd, int index)
{
	char	**args;
	char	*str_end;
	char	delimiter;
	int		offset;

	if (!*str_cmd)
		return (malloc_args(index));
	offset = 0;
	while (ft_isspace(*str_cmd))
		str_cmd++;
	delimiter = ' ';
	if (*str_cmd == '"' || *str_cmd == '\'')
	{
		delimiter = *str_cmd;
		str_cmd++;
		offset = 1;
	}
	str_end = str_cmd;
	while (*str_end && *str_end != delimiter)
		str_end++;
	args = get_command_args(str_end + offset, index + 1);
	args[index] = ft_substr(str_cmd, 0, str_end - str_cmd);
	return (args);
}
