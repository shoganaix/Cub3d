/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:47:46 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:41 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * It reallocs the string `dst` to make it big enough for the inplace join.
*/
char	*ft_strjoin_realloc(char **dst, const char *src)
{
	int		len_d;
	int		len_s;

	len_d = ft_strlen(*dst);
	len_s = ft_strlen(src);
	*dst = ft_str_realloc(*dst, len_d + len_s + 1, 0);
	if (!*dst)
		return (NULL);
	ft_strlcpy(*dst + len_d, src, len_s + 1);
	return (*dst);
}
