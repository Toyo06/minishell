/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:53:52 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 03:00:08 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var(char **arr, t_env **env)
{
	int		i;
	char	*path;

	i = 0;
	if (ft_getenv(env, arr[i]) != NULL)
		path = ft_strdup(ft_getenv(env, arr[i]));
	else
		path = ft_strdup("");
	i++;
	while (arr[i])
	{
		if (ft_getenv(env, arr[i]) != NULL)
			path = ft_strjoin(path, ft_getenv(env, arr[i]));
		i++;
	}
	ft_free_arr(arr);
	return (path);
}

char	*get_arg(char *equal, t_env **env)
{
	char	*arg;
	// char	*trimmed_arg;
	char	**env_vars;

	arg = ft_strdup(equal + 1);
	// trimmed_arg = ft_trim(arg);
	// free(arg);
	printf(RED "%s" CRESET "\n", arg);
	if (check_env_var(arg))
	{
		env_vars = ft_split(arg, '$');
		arg = get_env_var(env_vars, env);
	}
	return (arg);
}

char	*ft_trim(char *str)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 0;
	j = 0;
	trimmed = malloc(sizeof(char) * ft_strlen(str) - count_quotes(str) + 1);
	while (str[i])
	{
		while (str[i] == 34 || str[i] == 39)
			i++;
		if (str[i] == '\n')
			str[i] = ' ';
		trimmed[j] = str[i];
		i++;
		j++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}

int	count_quotes(char *str)
{
	int	i;
	int	count_quotes;

	i = 0;
	count_quotes = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			count_quotes++;
		i++;
	}
	return (count_quotes);
}

void	ft_export_bis(t_list **lst, t_env **env, int fd)
{
	t_list	*tmp;

	tmp = (*lst);
	(void)fd;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->data != 10 && tmp->data != 12)
			continue ;
		g_base.xport.eq_fl = 1;
		if (!check_arg_validity(tmp->arg))
			continue ;
		g_base.xport.eq = ft_strchr(tmp->arg, '=');
		if (g_base.xport.eq == NULL)
		{
			g_base.xport.eq_fl = 0;
			if (!check_arg_validity(tmp->arg))
				continue ;
			ft_update_export(env, tmp->arg, NULL, g_base.xport.eq_fl);
			continue ;
		}
		*g_base.xport.eq = '\0';
		g_base.xport.arg = get_arg(g_base.xport.eq, env);
		g_base.xport.arg = get_arg(g_base.xport.eq, env);
		ft_update_export(env, tmp->arg, g_base.xport.arg, g_base.xport.eq_fl);
		free(g_base.xport.arg);
	}
	exit_condition(0);
}
