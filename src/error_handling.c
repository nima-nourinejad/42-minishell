/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:00:59 by asohrabi          #+#    #+#             */
/*   Updated: 2024/05/24 13:27:21 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_token(char *cur)
{
	char	*token[7];
	int		index;

	token[0] = "|";
	token[1] = "<<<";
	token[2] = "<<";
	token[3] = "<";
	token[4] = ">>";
	token[5] = ">";
	token[6] = NULL;

	index = 0;

	while (token[index])
	{
		if (ft_strncmp(cur, token[index], ft_strlen(token[index])) == 0)
			return (token[index]);
		index++;
	}
	return (NULL);
}

int	accept_char(char *token, char *cur)
{
	if (same(token, "|"))
	{
		if (*cur == '|' || *cur == '\0')
			return (0);
	}
	else
	{
		if (find_token(cur) || *cur == '\0')
			return (0);
	}
	return (1);
}

char	*change_token(char *token, char *cur, int *index)
{
	char	*new_token;

	new_token = find_token(cur);
	if (new_token)
	{
		*index = *index + ft_strlen(new_token);
		return (new_token);
	}
	else
	{
		*index = *index + 1;
		if (*cur != ' ')
			return (NULL);
		else
			return (token);
	}
}

t_error	find_error(char *line)
{
	int		index;
	char	*token;
	char	*cur;
	int		len;
	t_error	error;

	index = 0;
	cur = line;
	len = (int)ft_strlen(line);
	token = NULL;
	error.cmd_counter = cmd_counter_error(line);
	error.index_cmd = 1;
	while (index <= len)
	{
		if (token)
		{
			if (!accept_char(token, cur + index))
			{
				error.index = index;
				if (cur[index] == '\0')
					error.error = ft_strdup("newline");
				else
					error.error = sliced_str(cur, index, index);
				return (error);
			}
		}
		token = change_token(token, cur + index, &index);
	}
	error.index = 0;
	error.error = NULL;
	return (error);
}

void	handle_heredoc_error(char *token, char *cur, t_error error)
{
	int		limiter_len;
	char	*line;
	char	*limiter;

	if (same(token, "<<"))
	{
		// printf("cmd_counter: %d, index_cmd: %d\n", error.cmd_counter, error.index_cmd);
		// if (error.cmd_counter != error.index_cmd)
		// 	printf("bash: syntax error near unexpected token `%s'\n", error.error);
		limiter_len = 0;
		while (cur[limiter_len] != ' ' && cur[limiter_len] !='\0'
			&& !find_token(cur + limiter_len))
			limiter_len++;
		limiter = malloc(limiter_len + 2);
		limiter[limiter_len] = '\n';
		limiter[limiter_len + 1] = '\0';
		ft_memcpy(limiter, cur, limiter_len);
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(0);
		while (!same(line, limiter))
		{
			free(line);
			ft_putstr_fd("> ", STDOUT_FILENO);
			line = get_next_line(0);
		}
		free(line);
		(void)error;
		// if (error.cmd_counter == error.index_cmd)
		// 	printf("bash: syntax error near unexpected token `%s'\n", error.error);
	}
}

char	*change_token_heredoc(char *token, char *cur, int *index, t_error error)
{
	char	*new_token;

	new_token = find_token(cur);
	if (new_token)
	{
		*index = *index + ft_strlen(new_token);
		return (new_token);
	}
	else
	{
		*index = *index + 1;
		if (*cur != ' ')
		{
			// if (error.cmd_counter == error.index_cmd)
			// {
				handle_heredoc_error(token, cur, error);
			// 	printf("bash: syntax error near unexpected token `%s'\n", error.error);
			// }
			// else
			// {
			// 	printf("bash: syntax error near unexpected token `%s'\n", error.error);
			// 	handle_heredoc_error(token, cur);
			// }
			return (NULL);
		}
		else
			return (token);
	}
}