/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:48:08 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:51 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		len;
	char	*ptr;

	len = ft_strlen(s1);
	start = 0;
	while (ft_strchr(set, s1[start]) && start < len)
	{
		start++;
	}
	len--;
	while (len > start && ft_strchr(set, s1[len]))
		len--;
	ptr = (char *)ft_calloc(len - start + 2, 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1 + start, len - start + 2);
	return (ptr);
}
