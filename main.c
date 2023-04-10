/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 08:07:25 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 18:12:26 by sroggens         ###   ########.fr       */
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
		g_base.main.k = 0;
		signal(SIGQUIT, sig_handler);
		signal(SIGINT, sig_handler);
		lst = NULL;
		g_base.sig.str = readline("\e[0;33mMinishell: \e[0m");
		if (!g_base.sig.str || checklinespace(g_base.sig.str) == 1)
			g_base.main.k = 1;
		if (!g_base.sig.str)
			break ;
		if (ft_strlen(g_base.sig.str) > 0 && g_base.main.k == 0)
			lunchingloopthings(&lst, &env);
	}
}
		//system("leaks minishell");

void	freeendofloop(t_list **lst)
{
	while ((*lst) && (*lst)->prev)
		(*lst) = (*lst)->prev;
	if (g_base.heredoc.totalrealheredoc > 0 && g_base.heredoc.sign == 0)
		unlinkheredoc();
	if (g_base.heredoc.totalheredoc > 0)
		free(g_base.heredoc.fdout);
	if (g_base.redir.totalred > 0)
		free(g_base.redir.fdout);
	(*lst) = free_list((*lst));
	free((*lst));
}

void	lunchingloopthings(t_list **lst, t_env **env)
{
	add_history(g_base.sig.str);
	if (op_count(g_base.sig.str) == 0)
		if (check_prompt(g_base.sig.str, lst, env)
			== 0 && g_base.op.liststate == 0)
			lunchingexec(lst, env);
	freeendofloop(lst);
}

void	lunchingexec(t_list **lst, t_env **env)
{
	g_base.path.totalpipe = checkpipes(lst);
	execution(lst, env, g_base.main.fd);
	if (g_base.sig.str != NULL)
		free(g_base.sig.str);
}

int	checklinespace(char *str)
{
	int	i;

	i = 0;
	g_base.rmquote.i = 0;
	g_base.rmquote.j = 0;
	g_base.err.count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
