/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:16:57 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/12 22:02:27 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkfilecannotbeopen(t_list **lst, char *str)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->data == 2)
		{
			if (access(tmp->next->arg, F_OK) != 0)
			{
				fileerror(&tmp);
				tmp = tmp->next;
				if (deletenodeforerror(&tmp) == 1)
				{
					free(str);
					return (1);
				}
				movelistiferror(lst);
				tmp = (*lst);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

void	fileerror(t_list **tmp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((*tmp)->next->arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
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

void	movelistiferror(t_list **lst)
{
	while ((*lst)->next && (*lst)->data != 6)
		(*lst) = (*lst)->next;
	(*lst) = (*lst)->next;
}

int	freestrerror(char *str)
{
	free(str);
	return (1);
}
