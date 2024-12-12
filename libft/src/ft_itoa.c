/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:43:56 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:12 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * It counts the digits of an integer.
 * Minus sign is also counted for negetive numbers
 * 
 * @param n
 * @return number of chars for the string representation of the int.
 * 			It is always at least 1.
*/
static int	ft_nbrlen(int n)
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
		n = n / 10;
	}
	return (len);
}

/**
 * Integer to string.
 * Using malloc(3), it generates a string that
 * represents the integer value given as argument.
 * Negative numbers are managed.
 * 
 * @param n integer to convert
 * @return string representing the number. 
 * 			NULL if memory allocation fails
*/
char	*ft_itoa(int n)
{
	int				len;
	char			*str;
	unsigned int	num;

	len = ft_nbrlen(n);
	str = (char *)ft_calloc(len + 1, 1);
	if (!str)
		return (NULL);
	else if (n < 0)
	{
		num = -1 * n;
		str[0] = '-';
	}
	else
		num = n;
	if (n == 0)
		str[0] = '0';
	len--;
	while (num > 0)
	{
		str[len--] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}
