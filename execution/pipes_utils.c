/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:03:08 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/19 20:52:34 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_base	g_base;

void	freeforpipe(void)
{
	int	i;

	i = 0;
	while (g_base.path.cmdfull[i])
	{
		free(g_base.path.cmdfull[i]);
		i++;
	}
	free(g_base.path.cmdfull);
	free(g_base.path.preppath);
	free(g_base.path.finalpath);
}

int	checkpipes(t_list **lst)
{
	int		pi;
	t_list	*tmp;

	tmp = (*lst);
	pi = 0;
	while (tmp)
	{
		if (tmp->data == 6)
			pi++;
		tmp = tmp->next;
	}
	return (pi);
}

void	mallocforthetabtoenv(t_env **env)
{
	t_env	*tmp;
	int		i;

	tmp = (*env);
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	g_base.path.envtab = malloc(sizeof(char *) * i + 1);
}

void	convertenvtotab(t_env **env)
{
	t_env	*tmp;
	int		i;

	if (!(*env))
		return ;
	tmp = (*env);
	i = 0;
	mallocforthetabtoenv(env);
	while (tmp->next)
	{
		g_base.path.envtab[i] = ft_strdup(tmp->name);
		g_base.path.envtab[i] = ft_strjoin(g_base.path.envtab[i], "=");
		g_base.path.envtab[i] = ft_strjoin(g_base.path.envtab[i], tmp->content);
		i++;
		tmp = tmp->next;
	}
	g_base.path.envtab[i] = NULL;
}
