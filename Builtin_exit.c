/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:01:53 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/28 11:35:44 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_exit(t_list **lst)
{
	t_list	*tmp;
	int		count;

	tmp = (*lst);
	count = 5;
	while (tmp)
	{
		count = ft_strlen(tmp->arg);
		if (count < 5)
			count = 5;
		if (ft_strncmp(tmp->arg, "exit", count) == 0
			&& tmp->prev == NULL && tmp->next == NULL)
			exit (0);
		tmp = tmp->next;
	}
}
