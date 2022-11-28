/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:17:35 by mayyildi          #+#    #+#             */
/*   Updated: 2022/11/28 15:42:24 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_base	g_base;

char	*check_path(char *cmd, char *envp_path)
{
	char	*cmd_path;
	char	**paths;
	int		i;

	paths = ft_split(envp_path, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return ("Error: invalid path");
}

char	*get_path(char *cmd, t_env **env)
{
	char	*envp_path;

	while (ft_strcmp((*env)->name, "PATH") != 0)
		(*env) = (*env)->next;
	envp_path = ft_strdup((*env)->content);
	return (check_path(cmd, envp_path));
}

void	ft_exec(char *arg, t_env **env)
{
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	printf("%s\n", arg);
	cmd = ft_split(arg, ' ');
	execve(cmd[0], cmd, NULL);
	path = get_path(cmd[0], env);
	if (!path)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		errormess(1);
	}
	if (execve(path, cmd, NULL) == -1)
		errormess(1);
}

void	cprocess(t_list **lst, t_env **env)
{
	char	*cmd;
	t_list	*tmp;

	tmp = *lst;
	cmd = ft_strdup((*lst)->arg);
	while (tmp->next && tmp->next->arg[0] == '-')
	{
		cmd = ft_strjoin(cmd, " ");
		cmd = ft_strjoin(cmd, tmp->next->arg);
		tmp = tmp->next;
		printf("%s\n", cmd);
	}
	ft_exec(cmd, env);
}

int	execcmd(t_list **lst, t_env **env)
{
	g_base.cmd.cpid = fork();
	if (g_base.cmd.cpid < 0)
		errormess(1);
	else if (g_base.cmd.cpid == 0)
		cprocess(lst, env);
	waitpid(g_base.cmd.cpid, NULL, 0);
	return (1);
}
