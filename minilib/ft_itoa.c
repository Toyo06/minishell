/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:12:31 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/07 20:36:22 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_itoa_size(long nbr)
{
	int		size;

	size = 1;
	if (nbr < 0)
		size++;
	while (nbr / 10 != 0)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

static void	ft_itoa_fill(char *sptr, int *index, long nbr)
{
	if (nbr >= 10)
	{
		ft_itoa_fill(sptr, index, nbr / 10);
		ft_itoa_fill(sptr, index, nbr % 10);
	}
	else
	{
		sptr[*index] = nbr + '0';
		(*index)++;
	}
}

char	*ft_itoa(int n)
{
	char	*sptr;
	int		index;
	long	nbr;

	nbr = n;
	sptr = (char *) ft_calloc(ft_itoa_size(nbr) + 1, 1);
	if (!sptr)
		return (NULL);
	index = 0;
	if (nbr < 0)
	{
		sptr[index++] = '-';
		nbr *= -1;
	}
	ft_itoa_fill(sptr, &index, nbr);
	sptr[index] = 0;
	return (sptr);
}
