/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:13:23 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/08 23:08:31 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	preparepathforexec(t_env **env, t_list **lst)
{
	t_env	*tmp;
	int		i;

	g_base.path.nbpath = 0;
	if (!(*env))
		return ;
	tmp = (*env);
	i = -1;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
			break ;
		if (tmp->next == NULL)
		{
			g_base.path.nbpath = 1;
			break ;
		}
		tmp = tmp->next;
	}
	g_base.path.preppath = ft_split(tmp->content, ':');
	while (g_base.path.preppath[++i])
		g_base.path.preppath[i] = ft_strjoin(g_base.path.preppath[i], "/");
	checkaccess(lst, env);
}

int	mallocfortab(t_list *tmp)
{
	int	i;

	i = 0;
	while (tmp && tmp->data != 6)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	tabforcmd(t_list **lst)
{
	t_list	*tmp;
	int		i;

	tmp = (*lst);
	g_base.path.cmdfull = malloc(sizeof(char *) * (mallocfortab(tmp) + 1));
	i = 0;
	while (tmp && tmp->data != 6 && check_builtin(tmp->arg) == 0)
	{
		while ((tmp->data == 11 || tmp->data == 3 || tmp->data == 4
				|| tmp->data == 13 || tmp->data == 15 || tmp->data == 12)
			&& tmp->next != NULL && tmp->next->data != 6)
			tmp = tmp->next;
		if ((tmp->data == 11 || tmp->data == 13 || tmp->data == 15)
			&& (tmp->next == NULL || tmp->next->data == 6))
			break ;
		g_base.path.cmdfull[i] = ft_strdup(tmp->arg);
		i++;
		tmp = tmp->next;
	}
	g_base.path.cmdfull[i] = NULL;
}

void	checkaccess(t_list	**lst, t_env **env)
{
	int		i;
	t_list	*tmp;

	(void)env;
	tmp = (*lst);
	i = 0;
	while (tmp->data == 11 || tmp->data == 3 || tmp->data == 4
		|| tmp->data == 13 || tmp->data == 12 || tmp->data == 15)
		tmp = tmp->next;
	if (access(tmp->arg, F_OK) == 0 || check_builtin(tmp->arg) == 1)
	{
		g_base.path.finalpath = ft_strdup(tmp->arg);
		while (g_base.path.preppath[i])
		{
			free(g_base.path.preppath[i]);
			i++;
		}
		return ;
	}
	else
		checkaccessbis(lst);
}
