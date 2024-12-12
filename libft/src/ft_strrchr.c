/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:11:45 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:42:44 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * The strrchr() function locates the last occurrence of c 
 * (converted to a char) in the string pointed to by s.  
 * The terminating null character is considered to be part of the string; 
 * therefore if c is `\0', the functions locate the terminating `\0'.
 * 
 * @param s string, where you are searching
 * @param c char you are searching for
 * @return pointer to the located character, 
 * or NULL if the character does not appear in the string.
*/
char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if ((unsigned char)s[len] == (unsigned char)c)
			return ((char *) &s[len]);
		len--;
	}
	return (0);
}
