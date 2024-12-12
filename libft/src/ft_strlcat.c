/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:16:36 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:46 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
	strlcpy() and strlcat() take the full size of the destination buffer and
	guarantee NUL-termination if there is room.  Note that room for the NUL
	should be included in dstsize.

	strlcat() appends string src to the end of dst.  It will append at most
	dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless
	dstsize is 0 or the original dst string was longer than dstsize (in prac-
	tice this should not happen as it means that either dstsize is incorrect
	or that dst is not a proper string).

	If the src and dst strings overlap, the behavior is undefined.
	
	RETURN VALUES
	the strlcpy() and strlcat() functions return the total
	length of the string they tried to create.  For strlcpy() that means the
	length of src.  For strlcat() that means the initial length of dst plus
	the length of src.

	If the return value is >= dstsize, the output string has been truncated.
	It is the caller's responsibility to handle this.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	j;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	j = 0;
	while (dstsize && src[j] != '\0' && (dst_len + j) < dstsize - 1)
	{
		dst[dst_len + j] = src[j];
		j++;
	}
	dst[dst_len + j] = '\0';
	return (dst_len + src_len);
}
