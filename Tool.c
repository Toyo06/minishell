/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:36:16 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/23 13:45:03 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*z;

	z = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*z = 0;
		z++;
		n--;
	}
}

void	*ft_calloc(size_t nbel, size_t size)
{
	void	*ptr;
	size_t	total;

	total = nbel * size;
	ptr = malloc(total);
	if (ptr == 0)
		return (ptr);
	ft_bzero(ptr, total);
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		lenword1;
	int		lenword2;
	char	*str;

	i = -1;
	if (s1 && s2)
	{
		lenword1 = ft_strlen(s1);
		lenword2 = ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * (lenword1 + lenword2 + 1));
		if (str == 0)
			return (0);
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
			str[lenword1 + i] = s2[i];
		str[lenword1 + i] = 0;
		free(s1);
		return (str);
	}
	return (NULL);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*dst;
	int		i;

	i = 0;
	if (!src)
		return (0);
	dst = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}
