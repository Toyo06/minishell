/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 08:07:25 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/19 17:48:03 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_base	g_base;

int	main(int argc, char **argv, char **envp)
{
	t_list	*lst;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = NULL;
	env_prep(envp, &env);
	register_pwd();
	convertenvtotab(&env);
	while (42)
	{
		signal(SIGQUIT, sig_handler);
		signal(SIGINT, sig_handler);
		lst = NULL;
		g_base.sig.str = readline("\e[0;33mMinishell: \e[0m");
		if (!g_base.sig.str)
		{
			lst = free_list(lst);
			free(lst);
			free(g_base.sig.str);
			break ;
			// ft_exit();
		}
		if (ft_strlen(g_base.sig.str) > 0)
		{
			add_history(g_base.sig.str);
			if (op_count(g_base.sig.str) == 0)
				if (check_prompt(g_base.sig.str, &lst, &env) == 1)
				{
					// if ((*lst).data == 1)
					// 	ft_readline((*lst).next->arg, 0);
					// if ((*lst).next != NULL && (*lst).next->data == 4 && (*lst).next->next != NULL)
					// 	simpleredir((*lst).arg, (*lst).next->next->arg);
					// if ((*lst).next != NULL && (*lst).next->data == 3 && (*lst).next->next != NULL)
					// 	doubleredir((*lst).arg, (*lst).next->next->arg);
					// dispatch_builtins(&lst, &env);
					g_base.path.totalpipe = checkpipes(&lst);
					execution(&lst, &env);
					// execcmd(&lst, &env);
				}
			lst = free_list(lst);
			free(lst);
		}
		free(g_base.sig.str);
		unlinkheredoc();
	}
}
