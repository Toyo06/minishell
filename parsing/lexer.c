/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:16:57 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/09 18:29:41 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_prompt(char *str, t_list **lst, t_env **env)
{
	int	i;
	int	comp;

	comp = 0;
	i = 0;
	g_base.op.liststate = 0;
	str = ft_strdup(str);
	if (check_forbidden_char(str) == 1 || check_quotes(str) == 0)
		return (1);
	else
	{
		if (ft_strlen(str) != countmallocnewstring(str))
			{
				comp = countmallocnewstring(str);
				str = addspacewhenneededpipe(str);
			}
		str = checkdol(str, env);
		if (str == NULL)
		{
			free(str);
			return (1);
		}
		prep_quotes(str);
		g_base.parsing.tab = ft_split(str, ' ');
		g_base.parsing.tab = revert_quotes(g_base.parsing.tab);
		while (g_base.parsing.tab[i])
		{
			g_base.parsing.tab[i] = rm_quote(g_base.parsing.tab[i], env);
			if (g_base.parsing.tab[i] == NULL)
				return (1);
			i++;
		}
		g_base.quote.returnvalue = list_prep(lst, g_base.parsing.tab, env);
		free(g_base.parsing.tab);	
		if (checkfilecannotbeopen(lst, str) == 1)
			return (1);
		if (err_management(lst) == 0 || checkererrorparsing(lst) == 1)
			return (1);
		while (deletenullarg(lst) == 1)	
			deletenullarg(lst);
	}
	if (str)
		free(str);
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

int	checkererrorparsing(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->data == 6 && (tmp->next == NULL || tmp->prev == NULL))
		{
			error_msg(3);
			return (1);
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

int	checkfilecannotbeopen(t_list **lst, char *str)
{
	t_list	*tmp;
	int	i;

	tmp = (*lst);
	i = 0;
	while (tmp)
	{
		if (tmp->data == 2)
		{
			if (access(tmp->next->arg, F_OK) != 0)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(tmp->next->arg, 2);
					ft_putstr_fd(": No such file or directory\n", 2);
					tmp->next->data = 20;
					tmp = tmp->next;
					if (deletenodeforerror(&tmp) == 1)
						{
							free(str);
							return (1);
						}
					while ((*lst) && (*lst)->data != 6)
						(*lst) = (*lst)->next;
					(*lst) = (*lst)->next;
					tmp = (*lst);
				}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	deletenodeforerror(t_list **lst)
{
	t_list	*tmp;
	t_list	*delete;

	tmp = (*lst);
	while (tmp->next != NULL && tmp->next->data != 6)
		tmp = tmp->next;
	while (tmp->prev != NULL && tmp->prev->data != 6)
	{
		delete = tmp;
		tmp = tmp->prev;
		if (delete->next != NULL)
			delete->prev->next = delete->next;
		else
			delete->prev->next = NULL;
		if (delete->next != NULL)
			delete->next->prev = delete->prev;
		delete->next = NULL;
		delete->prev = NULL;
		free(delete->arg);
		free(delete);
		if (tmp->next == NULL)
			return (1);
	}
	return (0);
}