/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:34:10 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:16 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
DESCRIPTION
     The memcmp() function compares byte string s1 against byte string s2.
     Both strings are assumed to be n bytes long.

RETURN VALUES
     The memcmp() function returns zero if the two strings are identical, oth-
     erwise returns the difference between the first two differing bytes
     (treated as unsigned char values, so that `\200' is greater than `\0',
     for example).  Zero-length strings are always identical.  This behavior
     is not required by C and portable code should only depend on the sign of
     the returned value.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*w1;
	char	*w2;

	w1 = (char *)s1;
	w2 = (char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n && w1[i] == w2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)w1[i] - (unsigned char)w2[i]);
}
