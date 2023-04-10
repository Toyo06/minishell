/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:27:47 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 02:47:11 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	register_pwd(void)
{
	g_base.pwd.pwd = getcwd(g_base.pwd.buf, sizeof(g_base.pwd.buf));
}

void	print_pwd(int fd)
{
	ft_putstr_fd(g_base.pwd.pwd, fd);
	ft_putstr_fd("\n", fd);
}

void	ft_pwd_p(t_list **lst, int fd)
{
	if ((*lst)->next == NULL)
		{
			if (g_base.pwd.pwd)
				print_pwd(fd);
			exit_condition(0);
			return ;
		}
		if ((*lst)->next->data == 10)
		{
			ft_putstr_fd("usage: pwd [-L | -P]\n", 2);
			exit_condition(1);
			g_base.retval.code = 1;
			return ;
		}
		else if ((*lst)->prev->data == 6)
		{
			if ((*lst)->next == NULL && g_base.pwd.pwd)
				print_pwd(fd);
			exit_condition(0);
			return ;
		}
		else
			err_msg_pwd(10);
}

void	ft_pwd(t_list **lst, int fd)
{
	if (ft_strcmp((*lst)->arg, PWD_P) == 0)
		ft_pwd_p(lst, fd);
	else if (ft_strcmp((*lst)->arg, "pwd") == 0)
	{
		if (g_base.pwd.pwd)
		{
			print_pwd(fd);
			exit_condition(0);
			return ;
		}
		else if ((*lst)->prev->data == 6 && (*lst)->next == NULL)
		{
			if (g_base.pwd.pwd)
				print_pwd(fd);
			exit_condition(0);
			return ;
		}
		else
			err_msg_pwd(10);
	}
}
