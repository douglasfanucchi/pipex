/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 04:38:07 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/02 04:38:08 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	clear_pipex(t_list **list, int *files, ...)
{
	char	**argv;
	va_list	ap;

	va_start(ap, files);
	argv = va_arg(ap, char **);
	va_end(ap);
	ft_closefd(2, files[0], files[1]);
	ft_lstclear(list, del_command);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		unlink(".tmp_here_doc");
}
