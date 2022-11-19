/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printf_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:59:30 by sroggens          #+#    #+#             */
/*   Updated: 2022/11/13 16:03:24 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	ft_printstr(char *str, int *count)
{
	int	i;

	i = -1;
	if (!str)
		str = "(null)";
	while (str[++i])
		ft_putcharprintf(str[i], count);
}

static void	ft_putnbrbase(long long nb, char *base, int *count)
{
	int	i;
	int	basewrite;

	i = 0;
	while (base[i])
		i++;
	if (nb < 0)
	{
		nb *= -1;
		ft_putcharprintf('-', count);
	}
	if (nb < i)
	{
		basewrite = nb % i;
		ft_putcharprintf(base[basewrite], count);
	}
	else if (nb >= i)
	{
		ft_putnbrbase(nb / i, base, count);
		ft_putnbrbase(nb % i, base, count);
	}
}

static void	ft_p(unsigned long long n, char *set, int *count)
{
	if (n > 15)
		ft_p(n / 16, set, count);
	ft_putcharprintf(set[n % 16], count);
}

void	ft_selectnextwords(va_list params, char txt, int *count)

{
	char	nexttowrite;

	if (txt == 'c')
	{
		nexttowrite = (char)va_arg(params, int);
		ft_putcharprintf(nexttowrite, count);
	}
	if (txt == 's')
		ft_printstr(va_arg(params, char *), count);
	if (txt == 'd' || txt == 'i')
		ft_putnbrbase(va_arg(params, int), "0123456789", count);
	if (txt == 'u')
		ft_putnbrbase(va_arg(params, unsigned int), "0123456789", count);
	if (txt == 'x' )
		ft_putnbrbase(va_arg(params, unsigned int), "0123456789abcdef", count);
	if (txt == 'X')
		ft_putnbrbase(va_arg(params, unsigned int), "0123456789ABCDEF", count);
	if (txt == '%')
		ft_putcharprintf(txt, count);
	if (txt == 'p')
	{
		ft_printstr("0x", count);
		ft_p(va_arg(params, unsigned long int), "0123456789abcdef", count);
	}
}
