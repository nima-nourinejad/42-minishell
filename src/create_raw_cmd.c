/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_raw_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:06:38 by nnourine          #+#    #+#             */
/*   Updated: 2024/04/19 10:55:51 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//error handing for | | or ||

char	**ft_create_raw_cmd(const char *input)
{
	char	**raw_cmd;

	raw_cmd = ft_split(input, '|');
	if (!raw_cmd)
		ft_master_clean(0, 0, 0, EXIT_FAILURE);
	return (raw_cmd);
}
