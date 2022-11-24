/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:27:13 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/24 11:52:00 by sroggens         ###   ########.fr       */
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

int	countmallocstr(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			if ((str[i + 1] == '<' && str[i] == '<')
				|| (str[i] == '>' && str[i + 1] == '>'))
				i++;
			count += 2;
		}
		i++;
	}
	return (ft_strlen(str) + count);
}

char	*addspace_be_foreop(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (countmallocstr(str) + 1));
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			new_str[j++] = ' ';
			new_str[j++] = str[i++];
			if ((str[i] == '>' && str[i - 1] == '>') || (str[i] == '<'
					&& str[i - 1] == '<'))
			{
				new_str[j++] = str[i++];
				new_str[j++] = ' ';
			}
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}
