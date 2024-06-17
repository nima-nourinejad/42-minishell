/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_temp_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:45:56 by nnourine          #+#    #+#             */
/*   Updated: 2024/06/17 14:50:57 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_pack	run_minishell(t_cmd *cmd)
{
	t_env_pack	env_pack;

	env_pack = init_env_pack(cmd);
	env_pack.original_env = export_original(cmd->original_env, 0);
	return (env_pack);
}

t_env	*set_start(t_env *env)
{
	char	*temp_str;
	char	*temp_str1;
	t_env	*temp_env;

	temp_env = env;
	while (temp_env && !same(temp_env->key, "SHLVL"))
		temp_env = temp_env->next;
	if (temp_env)
	{
		temp_str = temp_env->value;
		temp_env->value = ft_itoa(2);
		//protection
		free(temp_str);
	}
	else
	{
		temp_str1 = ft_itoa(1);
		//protection
		temp_str = ft_strdup("SHLVL");
		//protection
		add_node_front(&env, temp_str, temp_str1);
	}
	temp_env = env;
	// while (temp_env && !same(temp_env->key, "OLDPWD"))
	// 	temp_env = temp_env->next;
	// if (temp_env)
	// 	env = remove_node(env, temp_env);
	return (env);
}

t_env	*unset_oldpwd(t_env *env)
{
	t_env	*temp_env;

	temp_env = env;
	while (temp_env && !same(temp_env->key, "OLDPWD"))
		temp_env = temp_env->next;
	if (temp_env)
		env = remove_node(env, temp_env);
	return (env);
}
