/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:51:48 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/01 18:51:49 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

t_list	**get_commands(char **argv, char **envp)
{
	t_list		**commands;
	int			commands_start_at;
	char		**params;
	char		**paths;
	t_command	*command;

	paths = get_paths(envp);
	commands_start_at = 2;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		commands_start_at++;
	params = argv + commands_start_at;
	commands = ft_newlist();
	while (*(params + 1))
	{
		command = new_command(*(params), envp, paths);
		ft_lstadd_back(commands, ft_lstnew(command));
		params++;
	}
	del_paths(paths);
	return (commands);
}
