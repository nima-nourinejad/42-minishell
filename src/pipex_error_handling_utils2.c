/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_handling_utils2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:55:14 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/18 11:45:00 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_token_sq_dq(char **token, int *sq, int *dq, char c)
{
	if (c == '\"' && (*dq) == 0)
	{
		(*token) = NULL;
		(*dq) = 1;
	}
	else if (c == '\"')
		(*dq) = 0;
	else if (c == '\'' && (*sq) == 0)
	{
		(*token) = NULL;
		(*sq) = 1;
	}
	else if (c == '\'')
		(*sq) = 0;
}

static int	not_handling(char *token)
{
	return (same(token, "<<<") || same(token, "&&") || same(token, "\\")
		|| same(token, "||") || same(token, "*") || same(token, ";")
		|| same(token, "&") || same(token, "(") || same(token, ")")
		|| same(token, "<>") || same(token, "{") || same(token, "}")
		|| same(token, "[") || same(token, "]") || same(token, ":"));
}

static t_error	init_error(void)
{
	t_error	error;

	error.index = 0;
	error.error = NULL;
	error.not_handling = 0;
	return (error);
}

t_error	find_error_helper(char *line, char *token, int index, t_env_pack env_pack)
{
	t_error	error;

	error = init_error();
	if (not_handling(token))
	{
		error.not_handling = 1;
		error.error = ft_strdup(token);
		if (error.error == NULL)
		    clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
	}
	else if (!accept_char(token, line + index, env_pack))
	{
		error.index = index;
		if (line[index] == '\0')
		{
			error.error = ft_strdup("newline");
			if (error.error == NULL)
			    clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
		}
		else
		{
			if (find_token(line + index, env_pack))
				error.error = ft_strdup(find_token(line + index, env_pack));
			else
				error.error = sliced_str(line, index, index);
			if (error.error == NULL)
			    clean_all(env_pack.env, env_pack.original_env, NULL, NULL);
		}
	}
	return (error);
}

t_error_helper	init_error_helper(void)
{
	t_error_helper	helper;

	helper.token = NULL;
	helper.index = 0;
	helper.sq = 0;
	helper.dq = 0;
	helper.error = init_error();
	return (helper);
}
