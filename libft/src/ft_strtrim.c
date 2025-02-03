/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:48:08 by macastro          #+#    #+#             */
/*   Updated: 2025/02/03 15:09:20 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	c_in_set(char c, char const *set)
{
	return (ft_strchr(set, c) != NULL);
}

char	*ft_strtriml(char *s, char const *set)
{
	while (c_in_set(*s, set))
		s++;
	return (s);
}

char	*ft_strtrimr(char *s, char const *set)
{
	char	*back;

	back = s + ft_strlen(s);
	back--;
	while (c_in_set(*back, set))
		back--;
	*(back + 1) = '\0';
	return (s);
}

char	*ft_strtrim(char *s, char const *set)
{
	return (ft_strtrimr(ft_strtriml(s, set), set));
}
