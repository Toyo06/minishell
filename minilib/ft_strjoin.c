/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:29:01 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/09 22:26:39 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	setvalueforjoin();
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
	{
		g_base.strjoin.str = ft_strdup(s1);
		free(s1);
		return (g_base.strjoin.str);
	}
	g_base.strjoin.str = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1));
	if (g_base.strjoin.str == NULL)
		return (NULL);
	while (s1[g_base.strjoin.i])
	{
		g_base.strjoin.str[g_base.strjoin.i] = s1[g_base.strjoin.i];
		g_base.strjoin.i++;
	}
	while (s2[g_base.strjoin.j])
		g_base.strjoin.str[g_base.strjoin.i++] = s2[g_base.strjoin.j++];
	g_base.strjoin.str[g_base.strjoin.i] = '\0';
	free(s1);
	return (g_base.strjoin.str);
}

void	setvalueforjoin(void)
{
	g_base.strjoin.i = 0;
	g_base.strjoin.j = 0;
}
