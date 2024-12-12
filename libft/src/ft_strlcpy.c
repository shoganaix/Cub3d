/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:01:57 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:46 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
	strlcpy() and strlcat() take the full size of the destination buffer and
	guarantee NUL-termination if there is room.  Note that room for the NUL
	should be included in dstsize.

	strlcpy() copies up to dstsize - 1 characters from the string src to dst,
	NUL-terminating the result if dstsize is not 0.
	
	If the src and dst strings overlap, the behavior is undefined.

	RETURN VALUES
	the strlcpy() and strlcat() functions return the total
	length of the string they tried to create.  For strlcpy() that means the
	length of src.  For strlcat() that means the initial length of dst plus
	the length of src.

	If the return value is >= dstsize, the output string has been truncated.
	It is the caller's responsibility to handle this.
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dstsize && i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
