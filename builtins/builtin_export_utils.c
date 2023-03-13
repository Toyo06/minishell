/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:53:52 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/13 19:57:29 by mayyildi         ###   ########.fr       */
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

int	check_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*get_arg(char *equal, t_env **env)
{
	char	*arg;
	char	*trimmed_arg;
	char	**env_vars;

	arg = ft_strdup(equal + 1);
	trimmed_arg = ft_trim(arg);
	free(arg);
	if (check_env_var(trimmed_arg))
	{
		env_vars = ft_split(trimmed_arg, '$');
		trimmed_arg = get_env_var(env_vars, env);
	}
	return (trimmed_arg);
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

int	check_export_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			i++;
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	sp_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
