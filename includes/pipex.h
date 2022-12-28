/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 22:58:04 by dfanucch          #+#    #+#             */
/*   Updated: 2022/12/26 22:58:05 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <ft_printf.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>

typedef struct s_command {
	int		input_fd;
	int		output_fd;
	char	*pathname;
	char	*filename;
	char	**envp;
	char	**argv;
}	t_command;

t_command	*new_command(char *str_cmd, char **envp, char **paths);
void		del_command(t_command *command);
char		**get_paths(char **envp);
void		del_paths(char **paths);

#endif
