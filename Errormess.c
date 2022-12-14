/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errormess.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 03:31:13 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/28 11:41:18 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	errormess(int i)
{
	if (i == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n",
			2);
	if (i == 2)
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n",
			2);
	return ;
}
