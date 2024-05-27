/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:44:44 by nnourine          #+#    #+#             */
/*   Updated: 2024/05/27 17:52:14 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_2d_char(char **array)
{
	int		index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static size_t	strlen_modified(char *s)
{
	size_t	len;

	len = 0;
	if (s == 0 || *s == '\0')
		return (0);
	else
	{
		if (*s == '\"')
		{
			s++;
			while (*s != '\0' && *s != '\"')
			{
				len++;
				s++;
			}
			len += 2;
		}
		else if (*s == '\'')
		{
			s++;
			while (*s != '\0' && *s != '\'')
			{
				len++;
				s++;
			}
			len += 2;
		}
		else
		{
			while (*s != '\0' && !ft_isspace(*s) && !istoken(*s))
			{
				s++;
				len++;
			}
		}
		return (len);
	}
}

char	*strdup_modified(char *s, char *token)
{
	size_t	l;
	char	*d;

	l = ft_strlen(token);
	s = s + l;
	while (*s != '\0' && ft_isspace(*s))
		++s;
	l = strlen_modified(s);
	d = malloc((l + 1) * sizeof (char));
	if (d == 0)
		return (0);
	ft_memcpy (d, s, l);
	d[l] = '\0';
	// printf("d: %s\n", d);
	return (d);
}

char	*ft_remove(char *str, char *del, t_file *file)
{
	int		len1;
	int		len2;
	char	*part2;
	char	*temp;
	char	*result;
	int     original_len;

	original_len = ft_strlen(str);
	len1 = file->place;
	part2 = ft_strnstr(str, del, ft_strlen(str)) + ft_strlen(del);
	temp = part2;
	len2 = 0;
	while (*temp)
	{
		len2++;
		temp++;
	}
	result = malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_memcpy(result, str, len1);
	ft_memcpy(result + len1, part2, len2);
	result[len1 + len2] = '\0';
	free(str);
	file = file->next;
	while (file)
	{
		file->place = file->place + len1 + len2 - original_len;
		file = file->next;
	}
	return (result);
}
