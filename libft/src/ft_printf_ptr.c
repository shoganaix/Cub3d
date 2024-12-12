/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:03:40 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:20 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_ptr_len(unsigned long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		len++;
		n /= 16;
	}
	return (len);
}

static void	ft_putadr(unsigned long int n)
{
	if (n >= 16)
	{
		ft_putadr(n / 16);
		ft_putadr(n % 16);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd(n + '0', 1);
		else if (n >= 10)
			ft_putchar_fd((n - 10) + 'a', 1);
	}
}

/**
 * It prints the address in hexadecimal format 0xNUM.
 * Possible flags: "-w"
 * @returns number of printed chars
*/
int	print_pointer(void *pointer_addr, t_cs sc)
{
	int		len;
	int		pad;

	len = ft_ptr_len((unsigned long int) pointer_addr) + 2;
	pad = 0;
	print_padding(1, sc, &pad, len);
	ft_putstr_fd("0x", 1);
	ft_putadr((unsigned long int) pointer_addr);
	print_padding(0, sc, &pad, len);
	return (len + pad);
}
