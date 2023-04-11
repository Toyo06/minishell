/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:23:51 by mayyildi          #+#    #+#             */
/*   Updated: 2023/02/09 09:26:59 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*dst;

	dst = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		dst[j] = s1[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst);
}
