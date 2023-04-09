/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipesbis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:09:54 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/09 22:09:56 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_list **lst, t_env **env)
{
	int	retval;

	retval = 0;
	g_base.retval.pcd = 0;
	g_base.retval.inp = 0;
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
		executionstart(lst, env);
	if (checkpipes(lst) == 1)
		execonepipe(lst, env);
	if (checkpipes(lst) > 1)
		pipeline(env, lst);
}
