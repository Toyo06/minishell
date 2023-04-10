/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:06:40 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 02:48:51 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_empty(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->data == 10)
			return (0);
		else if (tmp->data == 6)
		{
			while ((*lst)->data == 6)
				(*lst) = (*lst)->next;
			(*lst) = (*lst)->next;
			(*lst) = (*lst)->next;
			tmp = (*lst);
		}
		if (tmp->next == NULL)
			return (1);
		tmp = tmp->next;
	}
	return (1);
}

void	execution(t_list **lst, t_env **env, int fd)
{
	int	retval;

	retval = 0;
	g_base.retval.pcd = 0;
	g_base.retval.inp = 0;
	g_base.xport.disp2 = 0;
	redirection(lst);
	countheredoc(lst);
	while (1)
	{
		retval = heredoc(lst);
		if (retval == 1)
			break ;
		if (retval == 2)
			return ;
	}
	if (checkpipes(lst) == 0)
	{
		// isitabuiltin(lst, env, fd);
		dispatch2(lst, env, fd);
		execsimglecmd(lst, env, fd);
	}
	if (checkpipes(lst) == 1)
		execonepipe(lst, env, fd);
	if (checkpipes(lst) > 1)
		pipeline(env, lst, fd);
}
