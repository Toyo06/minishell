/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:15:07 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 16:09:55 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	arr_count(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

static char	*ft_copy(char const *s, char c)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	str = malloc(sizeof(*str) * (i + 1));
	if (!str)
		return (NULL);
	while (s[j] && j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		cut;
	char	**arr;

	if (!s)
		return (NULL);
	cut = arr_count(s, c);
	arr = malloc(sizeof(*arr) * (cut + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			arr[i++] = ft_copy(s, c);
			while (*s && *s != c)
				s++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
