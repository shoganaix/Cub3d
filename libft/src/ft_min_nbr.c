/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:29:07 by macastro          #+#    #+#             */
/*   Updated: 2023/09/15 18:29:09 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_min_nbr(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

int	ft_min_arrint(int *ints, int n)
{
	int	i;
	int	min;

	if (n == 0)
		return (-999);
	min = ints[0];
	i = 0;
	while (i < n)
	{
		if (ints[i] < min)
			min = ints[i];
		i++;
	}
	return (min);
}
