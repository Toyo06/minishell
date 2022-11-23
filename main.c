/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:27:13 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/23 13:16:15 by sroggens         ###   ########.fr       */
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
	printthelistenv(&env);
	while (42)
	{
		lst = NULL;
		str = readline("\033[0;32m Ce minishell de bg :");
		if (ft_strlen(str) > 0)
			add_history(str);
		checkthestart(str, &lst);
		printthelist(&lst);
		free(str);
		lst = freelist(lst);
		free(lst);
		system("leaks lexer");
	}
}
