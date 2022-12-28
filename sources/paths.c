/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:51:26 by dfanucch          #+#    #+#             */
/*   Updated: 2022/12/28 11:51:27 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static char	*find_path_row(char **envp)
{
	while (!ft_strnstr(*envp, "PATH", 4))
		envp++;
	return (ft_strdup(*envp));
}

char	**get_paths(char **envp)
{
	char	*path;
	char	**paths;

	path = find_path_row(envp);
	paths = ft_split(path + 5, ':');
	free(path);
	return (paths);
}

void	del_paths(char **paths)
{
	char	**t_paths;

	t_paths = paths;
	while (*t_paths)
	{
		free(*t_paths);
		t_paths++;
	}
	free(paths);
}
