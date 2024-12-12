/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_realloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:47:46 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:38 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * A realloc for str. 
 * 
 * How it works:
 * - creates a new allocation, 
 * - copies as much of the old data pointed to by ptr as will fit to 
 	the new allocation, 
 * - frees the old allocation, and returns a pointer to the allocated memory.  
 * 
 * Extreme cases:
 * - If str is NULL, realloc() is identical to a call to malloc() for size bytes.
 * - If size is zero and str is not NULL, a new minimum sized object 
 * (NULL for str) is allocated and the original object is freed. 
 * 
 * @param str string to realloc
 * @param size new size of the string (smaller or bigger) including null 
 * terminator. If size is smaller the new string contents as much as it can.
 * @param offset if you want the new content of the string to start with 
 * an offset.
 * @return a new char pointer with the reallocated string
*/
char	*ft_str_realloc(char *str, size_t size, int offset)
{
	char	*new;

	if (!str)
	{
		new = (char *)malloc(sizeof(char) * size);
		if (!new)
			return (NULL);
		return (new);
	}
	if (size == 0 && str)
	{
		new = NULL;
		free(str);
		return (new);
	}
	new = (char *)malloc(sizeof(char) * size);
	if (!new)
		return (NULL);
	ft_strlcpy(new, str + offset, ft_min_nbr(ft_strlen(str)+1, size));
	free(str);
	return (new);
}
