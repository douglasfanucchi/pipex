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
	ft_closefd(2, files[0], files[1]);
	ft_lstclear(list, del_command);
}
