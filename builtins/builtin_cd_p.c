/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:39:41 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/28 20:39:48 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd_p(t_list **lst)
{
	if ((*lst)->next)
		if (chdir((*lst)->next->arg) == -1)
			handle_err(8);
	exit_condition(0);
	return ;
}
