/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:35:45 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:21 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putarr_ints(int *ints, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%i\n", ints[i]);
		i++;
	}
}

void	ft_putarr_str(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		ft_printf("%s\n", words[i]);
		i++;
	}
}
