/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:47:35 by macastro          #+#    #+#             */
/*   Updated: 2023/10/04 19:47:36 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * For each char in the string 's', it applies the function 'f'
 * giving as paramemeters the index of each char within 's' and 
 * the address of each char itself, which could be modified if necessary.
 * // address: &s[i] or s+i
 * @param s the string to iterate
 * @param f the function to apply over each char
 * @return void
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
