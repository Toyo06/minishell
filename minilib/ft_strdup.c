/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:23:51 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/13 21:30:02 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*dst;

	if (!s1)
		return (NULL);
	dst = malloc(sizeof(char) * ft_strlen(s1) + 1);
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
