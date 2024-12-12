/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:47:21 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:37 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_count_words(const char *s, char sep)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		if (*s)
			count++;
		while (*s && *s != sep)
			s++;
	}
	return (count);
}

/**
 * duplicate the string ending with 'c' pointed by 'src' on the 
 * specified address 'dst'.
 * @return the len of the duplicated split, returns -1 if memory fails
*/
static int	ft_dupstop(char **dst, const char *src, char c)
{
	int	len;

	len = 0;
	while (src[len] && src[len] != c)
		len++;
	*dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!*dst)
		return (-1);
	ft_strlcpy(*dst, src, len + 1);
	return (len);
}

/**
 * It allocates memory using malloc(3) for an array of strings
 * which is the result of dividing the string 's' in substrings 
 * using the char 'c' as delimiter. The array should end with 
 * a NULL pointer.
*/
char	**ft_split(char const *s, char c)
{
	char	**dirs;
	int		dir_j;
	int		wj_len;

	dirs = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!dirs)
		return (0);
	dir_j = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			wj_len = ft_dupstop(&dirs[dir_j++], s, c);
			if (wj_len < 0)
			{
				ft_free_arrstr(dirs);
				return (NULL);
			}
			s += wj_len;
		}
	}
	dirs[dir_j] = 0;
	return (dirs);
}

int	ft_count_arrstr(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		i++;
	return (i);
}
