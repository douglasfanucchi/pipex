/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:21:33 by dfanucch          #+#    #+#             */
/*   Updated: 2022/12/28 13:21:34 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

t_list	**get_commands(char **argv, char **envp)
{
	t_list		**commands;
	t_command	*command;
	char		**paths;
	char		**str_cmds;
	int			i;

	str_cmds = argv + 1;
	i = 1;
	paths = get_paths(envp);
	commands = ft_newlist();
	if (!commands)
		return (NULL);
	while (i < 3)
	{
		command = new_command(str_cmds[i], envp, paths);
		ft_lstadd_back(commands, ft_lstnew(command));
		i++;
	}
	del_paths(paths);
	return (commands);
}
