/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:44:55 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/13 15:46:44 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	countword(char *str, char del)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == del)
			i++;
		if (str[i] != 0)
			count++;
		while (str[i] && str[i] != del)
			i++;
	}
	return (count);
}

static char	*writeword(char *str, char del)
{
	char	*strwrited;
	int		i;
	int		len;

	len = 0;
	while (str[len] && str[len] != del)
		len++;
	strwrited = (char *)malloc(sizeof(char) * (len + 1));
	if (!strwrited)
		return (NULL);
	i = 0;
	while (i < len)
	{
		strwrited[i] = str[i];
		i++;
	}
	strwrited[i] = 0;
	return (strwrited);
}

static char	*freel(int i, char *str, char del, char **tab)
{
	tab[i] = writeword(str, del);
	if (!tab[i])
	{
		while (i > 0)
		{
			i--;
			free(tab[i]);
		}
		free(tab);
		return (NULL);
	}
	return (tab[i]);
}

char	**ft_split(char const *s, char c)
{
	int		word;
	int		i;
	char	**tab;

	if (!s)
		return (NULL);
	i = 0;
	word = countword((char *)s, c);
	tab = (char **)malloc(sizeof(char *) * (word + 1));
	if (!tab)
		return (NULL);
	while (i < word)
	{
		while (*s == c)
			s++;
		if (*s != 0)
			tab[i] = freel(i, (char *)s, c, tab);
		while (*s && *s != c)
			s++;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
