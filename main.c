/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 08:07:25 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/22 10:31:56 by mayyildi         ###   ########.fr       */
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
		}
		if (ft_strlen(g_base.sig.str) > 0)
		{
			add_history(g_base.sig.str);
			if (op_count(g_base.sig.str) == 0)
				if (check_prompt(g_base.sig.str, &lst, &env) == 1)
				{
					g_base.path.totalpipe = checkpipes(&lst);
					execution(&lst, &env);
				}
			while (lst->prev) {
				lst = lst->prev;
			}
			lst = free_list(lst);
			free(lst);
			unlinkheredoc();
		}
		free(g_base.sig.str);

	}
}
