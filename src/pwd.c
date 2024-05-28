/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:26:11 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/28 12:02:07 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	run_pwd(t_cmd *cmd)
{
	t_env_pack	env_pack;
	char		*path;

	path = NULL;
	env_pack = init_env_pack(cmd);
	path = getcwd(NULL, 0);
	//maybe protection against failure
	// printf("%s\n", path);
	ft_putendl_fd(path, 1);
	free(path);
	export_original(env_pack.original_env, 0);
	return (env_pack);
}

