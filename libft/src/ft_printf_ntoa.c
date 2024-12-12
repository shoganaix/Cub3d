/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ntoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:22:34 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:20 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_nbrlen(long long n, int b)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n = n / b;
	}
	return (len);
}

/**
 * returns new string with the number in base _base_
 * if number is integer, see ft_itoa
 * (review for libft)
*/
char	*ft_number_to_base(unsigned long long n, char *base, int b)
{
	int					len;
	char				*word;
	unsigned long long	num;

	len = ft_nbrlen(n, b);
	word = (char *)ft_calloc(len + 1, 1);
	if (!word)
		return (NULL);
	num = n;
	if (n == 0)
		word[0] = '0';
	len--;
	while (num > 0)
	{
		word[len--] = base[num % b];
		num = num / b;
	}
	return (word);
}

char	*number_to_strhex(unsigned long long number, int mayus)
{
	char		*addr_str;

	if (mayus)
		addr_str = ft_number_to_base(number, HEXMAY, 16);
	else
		addr_str = ft_number_to_base(number, HEXMIN, 16);
	return (addr_str);
}

char	*number_to_strdec(long long number)
{
	char		*addr_str;
	const char	dec_chars[10] = "0123456789";

	addr_str = ft_number_to_base(number, (char *)dec_chars, 10);
	return (addr_str);
}
