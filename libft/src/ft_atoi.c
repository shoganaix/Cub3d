/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:09:09 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:39:12 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
	The atoi() function converts the initial portion of the string pointed to
    by str to int representation.
	Positive numbers can have sign ('+') or not.
*/
int	ft_atoi(const char *str)
{
	int	i;
	int	number;
	int	sign;

	number = 0;
	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		number = number * 10 + sign * (str[i] - '0');
		i++;
	}
	return (number);
}

int	ft_atoi_hex(const char *str, int b)
{
	int	i;
	int	number;
	int	sign;

	number = 0;
	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (ft_isdigit(str[i])
		|| ('A' <= ft_toupper(str[i]) && ft_toupper(str[i]) <= 'F'))
	{
		if (ft_isdigit(str[i]))
			number = number * b + sign * (str[i] - '0');
		else
			number = number * b + sign * (ft_toupper(str[i]) - 'A' + 10);
		i++;
	}
	return (number);
}

/**
 * Is the number represented out of int type limits?
 * 1 - yes
 * 0 - no
*/
int	is_gt_int_limits(char *num_as_word)
{
	int	len;
	int	i;

	i = 0;
	if (num_as_word[0] == '-')
		i++;
	while (num_as_word[i] == '0')
		i++;
	len = ft_strlen(&num_as_word[i]);
	if (len > 10)
		return (1);
	if (len == 10)
	{
		if (num_as_word[0] == '-')
		{
			if (ft_strncmp(&num_as_word[1], "2147483648", 10) > 0)
				return (1);
		}
		else
		{
			if (ft_strncmp(num_as_word, "2147483647", 10) > 0)
				return (1);
		}
	}
	return (0);
}

/**
 * safe atoi.
 * It saves the integer in the memory given by `n`.
 * The string `word` must contain only digits.
 * It does not accept '+' as sign.
 * Returns TRUE if success, FALSE otherwise.
*/
t_bool	ft_atoi_secure(char *word, int *n)
{
	int	i;

	i = 0;
	if (!word)
		return (FALSE);
	if (word[i] == '-')
		i++;
	if (!word[i])
		return (FALSE);
	while (word[i])
		if (!ft_isdigit(word[i++]))
			return (FALSE);
	if (is_gt_int_limits(word))
		return (FALSE);
	*n = ft_atoi(word);
	return (TRUE);
}
