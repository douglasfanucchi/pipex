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
