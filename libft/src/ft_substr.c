/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:48:18 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:51 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	min_sizes(size_t n1, size_t n2)
{
	if (n1 <= n2)
		return (n1);
	else
		return (n2);
}

/**
 * It allocates memory (malloc) and returns a substring of the string 's'.
 * The substring starts at index 'start' and has a maximum length of 'len'.
 * 
 * @param s string from which to create the substring
 * @param start index of the character in the string where the substring starts
 * @param len the maximum length of the substring
 * @returns the substring. NULL if memory fails.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	s_len;
	unsigned int	ss_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		substr = (char *)malloc(1);
		if (!substr)
			return (NULL);
		substr[0] = 0;
		return (substr);
	}
	ss_len = min_sizes(len, s_len - start);
	substr = (char *)malloc(sizeof(char) * (ss_len +1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, ss_len + 1);
	return (substr);
}
