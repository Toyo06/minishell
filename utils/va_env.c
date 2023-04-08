/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:12:52 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/08 23:01:36 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	va_env(t_list **lst, t_env **env)
{
	t_list	*tmp;

	tmp = (*lst);
	(void)env;
	while (tmp)
	{
		if (tmp->data == 9)
		{
			if (tmp->arg[1] == '\0')
			{
				free(tmp->arg);
				tmp->arg = NULL;
			}
			tmp->data = 10;
		}
		tmp = tmp->next;
	}
	tmp = (*lst);
}

void	va_convert(t_list **lst)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split((*lst)->arg,'$');
	free((*lst)->arg);
	if (tmp[1] == NULL)
		(*lst)->arg = ft_strdup(tmp[0]);
	else
		(*lst)->arg = ft_strjoin(tmp[0], tmp[1]);
	(*lst)->data = 10;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

char	*va_search(char *new_str, t_env **env, char **arr)
{
	t_env	*tmp;
	int		i;

	tmp = (*env);
	i = 0;
	while (arr[i])
	{
		while (tmp)
		{
			if (ft_strcmp(arr[i], tmp->name) == 0)
			{
				if (new_str == NULL)
					new_str = ft_strdup(tmp->content);
				else
					new_str = ft_strjoin(new_str, tmp->content);
				break ;
			}
			tmp = tmp->next;
		}
		tmp = (*env);
		i++;
	}
	return (new_str);
}

char	*cpy_until_dollar(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[j] != '$')
		j++;
	new_str = malloc(sizeof(char) * j + 1);
	while (str[i] != '$')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*cpy_after_dollar(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i] != '$')
		i++;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - i));
	while (str[i])
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}
