/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:13:23 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/11 17:31:36 by mayyildi         ###   ########.fr       */
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
			g_base.retval.code = 127;
			break ;
		}
		tmp = tmp->next;
	}
	g_base.path.preppath = ft_split(tmp->content, ':');
	while (g_base.path.preppath[++i])
		g_base.path.preppath[i] = ft_strjoin(g_base.path.preppath[i], "/");
	checkaccess(lst);
}

void	tabforcmd(t_list **lst)
{
	t_list	*tmp;
	int		i;

	tmp = (*lst);
	i = 0;
	while (tmp && tmp->data != 6)
	{
		tmp = tmp->next;
		i++;
	}
	g_base.path.cmdfull = malloc(sizeof(char *) * (i + 1));
	tmp = (*lst);
	i = 0;
	while (tmp && tmp->data != 6)
	{
		g_base.path.cmdfull[i] = ft_strdup(tmp->arg);
		i++;
		tmp = tmp->next;
	}
	g_base.path.cmdfull[i] = NULL;
}

void	checkaccess(t_list	**lst)
{
	// t_list	*tmp;
	int		i;

	// tmp = (*lst);
	i = 0;
	if (access((*lst)->arg, F_OK) == 0)
	{
		g_base.path.finalpath = ft_strdup((*lst)->arg);
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

void	checkaccessbis(t_list **lst)
{
	int		i;
	t_list	*tmp;

	i = -1;
	tmp = (*lst);
	while (g_base.path.preppath[++i])
	{
		g_base.path.finalpath = ft_strjoin(g_base.path.preppath[i], tmp->arg);
		if (access(g_base.path.finalpath, F_OK) == 0)
		{
			i++;
			while (g_base.path.preppath[i])
			{
				free(g_base.path.preppath[i]);
				i++;
			}
			break ;
		}
		free(g_base.path.finalpath);
		if (g_base.path.preppath[i + 1] == NULL)
		{
			g_base.path.finalpath = NULL;
			printf(RED "%d" CRESET "\n", g_base.retval.code);
			if (g_base.path.nbpath == 1)
			{
				printf("Minishell: %s: No such file or directory\n", (*lst)->arg);
				g_base.retval.code = 127;
			}
			else
			{
				printf("minishell: %s: command not found\n", (*lst)->arg);
				g_base.retval.code = 1;
			}
		}
	}
}

