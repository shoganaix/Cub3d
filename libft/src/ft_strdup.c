/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:50:05 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:40 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
	The strdup() function allocates sufficient memory for a copy of the
	string s1, does the copy, and returns a pointer to it.  The pointer may
	subsequently be used as an argument to the function free.

	If insufficient memory is available, NULL is returned and errno is set to
	ENOMEM.
*/
char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		len;
	int		i;

	len = ft_strlen(s1);
	dup = (char *)ft_calloc((len + 1), sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
