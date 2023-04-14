/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_prep_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:37:13 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/14 23:26:19 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*find_next_valid_node(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp && (tmp->data == 11 || tmp->data == 3
			|| tmp->data == 4 || tmp->data == 13
			|| tmp->data == 12 || tmp->data == 15))
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void	free_preppath_from_index(int index)
{
	while (g_base.path.preppath[index])
	{
		free(g_base.path.preppath[index]);
		index++;
	}
}

void	path_not_found(t_list **lst)
{
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

void	checkaccessbis(t_list **lst)
{
	int		i;
	t_list	*tmp;

	tmp = find_next_valid_node(lst);
	if (tmp == NULL || tmp->data == 6)
		return ;
	i = -1;
	if (g_base.path.preppath == NULL)
	{
		g_base.path.finalpath = NULL;
		path_not_found(lst);
		return ;
	}
	while (g_base.path.preppath[++i])
		if (cutingacessbis(&tmp, i, lst) == 0)
			break ;
}

int	cutingacessbis(t_list **tmp, int i, t_list **lst)
{
	if ((*tmp)->arg[0] == '/' && access((*tmp)->arg, F_OK) != 0)
			g_base.path.finalpath = ft_strdup((*tmp)->arg);
	else
		g_base.path.finalpath
			= ft_strjoin(g_base.path.preppath[i], (*tmp)->arg);
	if (access(g_base.path.finalpath, F_OK) == 0)
	{
		i++;
		free_preppath_from_index(i);
		return (0);
	}
	free(g_base.path.finalpath);
	if (g_base.path.preppath[i + 1] == NULL)
	{
		g_base.path.finalpath = NULL;
		path_not_found(lst);
	}
	return (1);
}
