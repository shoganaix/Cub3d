/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:47:46 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:43 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * Returns a new string (malloc) after concatenating both given strings.
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	len;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)ft_calloc((len + 1), sizeof(char));
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, ft_strlen(s1) + 1);
	ft_strlcat(joined, s2, len + 1);
	return (joined);
}

/**
 * Returns a the same s1 pointer, but now pointing to the concatenation.
 * Memory safe (it makes a free of the previous value);
*/
char	*ft_strjoin_inplace(char **s1, const char *s2)
{
	char	*joined;

	joined = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = joined;
	return (*s1);
}

/**
 * Returns a the same s1 pointer, but now pointing to the concatenation.
 * Memory safe (it makes a free of the previous value);
 * And also frees s2.
*/
char	*ft_strjoin_inplace2(char **s1, char **s2)
{
	char	*joined;

	joined = ft_strjoin(*s1, *s2);
	free(*s1);
	free(*s2);
	*s1 = joined;
	return (*s1);
}

/**
 * Append a char to a string. It returns a new string with str+c
*/
char	*ft_strappendc(char *s1, const char c)
{
	const char	s2[] = {c, '\0'};

	return (ft_strjoin(s1, s2));
}

/**
 * Append a char to a string, inplace. Accepts NULL as s1.
*/
char	*ft_strappendc_inplace(char *s1, const char c)
{
	const char	s2[] = {c, '\0'};

	if (!s1)
	{
		s1 = malloc(2 * sizeof(char));
		ft_strlcpy(s1, s2, 2);
		return (s1);
	}
	return (ft_strjoin_inplace(&s1, s2));
}
