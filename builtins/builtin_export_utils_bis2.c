/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils_bis2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:33:05 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 21:33:16 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_export_eq(t_list *tmp, t_env **env)
{
	*g_base.xport.eq = '\0';
	g_base.xport.arg = get_arg(g_base.xport.eq, env);
	ft_update_export(env, tmp->arg, g_base.xport.arg, g_base.xport.eq_fl);
	free(g_base.xport.arg);
}
