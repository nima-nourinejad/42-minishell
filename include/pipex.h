/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:57:03 by asohrabi          #+#    #+#             */
/*   Updated: 2024/04/26 13:51:21 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/libft.h"
# include "../include/minishell.h"
# include "minishell.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <string.h>

void	error(int status);
void	ft_free(char **array);
size_t	find_max(char *str1, char *str2);

void	here_doc(char *limiter);
void	clean_cmd(char *str);
int		open_file(char *argv, int i);
//void	execute_cmd(t_cmd *cmd_start, t_cmd *cmd_execution);

#endif