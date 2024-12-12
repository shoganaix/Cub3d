/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:11:45 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:50 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
	The strnstr() function locates the first occurrence of the null-termi-
	nated string needle in the string haystack, where not more than len char-
	acters are searched.  Characters that appear after a `\0' character are
	not searched.

	RETURN VALUES
	If needle is an empty string, haystack is returned; if needle occurs
	nowhere in haystack, NULL is returned; otherwise a pointer to the first
	character of the first occurrence of needle is returned.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;
	size_t	len_haystack;
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)(haystack));
	len_needle = ft_strlen(needle);
	len_haystack = ft_strlen(haystack);
	i = 0;
	if ((int)len_haystack - (int)len_needle < 0)
		return (0);
	while (i <= len_haystack - len_needle && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j]
			&& needle[j] != '\0' && i + j < len)
		{
			j++;
		}
		if (j == len_needle)
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}
