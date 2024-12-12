/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:09:09 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:03 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_countchr(const char *str, char c, size_t n)
{
	size_t	len;
	size_t	i;
	int		count;

	count = 0;
	len = ft_strlen(str);
	if (len < n)
		n = len;
	i = 0;
	while (i < n)
		if (str[i++] == c)
			count++;
	return (count);
}
