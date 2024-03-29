/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerbis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:08:45 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/15 14:17:19 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	check_prompt(char *str, t_list **lst, t_env **env)
{
	g_base.op.liststate = 0;
	if (check_forbidden_char(str) == 1 || check_quotes(str) == 0)
		return (1);
	else
	{
		if (ft_strlen(str) != countmallocnewstring(str))
			str = addspacewhenneededpipe(str);
		str = checkdol(str, env);
		if (str == NULL)
			return (freestrerror(str));
		if (splitingforquote(str) == 1)
			return (1);
		g_base.quote.returnvalue = list_prep(lst, g_base.parsing.tab);
		free(g_base.parsing.tab);
		if (errorset(lst) == 1 || checkfilecannotbeopen(lst, str) == 1)
			return (1);
		if (err_management(lst) == 0 || checkererrorparsing(lst) == 1)
			return (1);
		while (deletenullarg(lst) == 1)
			deletenullarg(lst);
	}
	free(str);
	return (0);
}

int	splitingforquote(char *str)
{
	int	i;

	i = 0;
	prep_quotes(str);
	g_base.parsing.tab = ft_split(str, ' ');
	g_base.parsing.tab = revert_quotes(g_base.parsing.tab);
	while (g_base.parsing.tab[i])
	{
		g_base.rmquote.i = 0;
		g_base.rmquote.j = 0;
		g_base.parsing.tab[i] = rm_quote(g_base.parsing.tab[i]);
		if (g_base.parsing.tab[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}

int	deletenullarg(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->arg == NULL && (tmp->next != NULL || tmp->prev != NULL))
			return (freenullargbis(&tmp));
		else if (tmp->arg == NULL)
		{
			g_base.op.liststate = 1;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	freenullargbis(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	if (tmp->next == NULL)
	{
		tmp->prev->next = NULL;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
		return (1);
	}
	else
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
		return (1);
	}
	return (1);
}
