/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:27:13 by sroggens          #+#    #+#             */
/*   Updated: 2022/12/01 14:04:34 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_base	g_base;

void	rl_replace_line(const char *text, int clear_undo);

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_list	*lst;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = NULL;
	prepaenv(envp, &env);
	registerpwd(&env);
	while (42)
	{
		lst = NULL;
		str = readline("\033[0;32m bruh: ");
		if (ft_strlen(str) > 0)
			add_history(str);
		if (checkthestart(str, &lst))
		{
			check_heredoc(&lst);
			execcmd(&lst, &env);
		}
		ft_pwd(&lst);
		ft_env(&env, &lst);
		free(str);
		lst = freelist(lst);
		free(lst);
		// system("leaks lexer");
	}
}
