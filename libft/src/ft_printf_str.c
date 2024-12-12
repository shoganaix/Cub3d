/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:58:15 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:21 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	print_char(char c, t_cs sc, int fd)
{
	int	len;
	int	pad;

	len = 1;
	pad = 0;
	print_padding(1, sc, &pad, len);
	ft_putchar_fd(c, fd);
	print_padding(0, sc, &pad, len);
	return (len + pad);
}

/**
 * possible flags: "-w.prec" 
 * Precision is dealt first, then "-w".
 * @returns number of printed chars
*/
int	print_str(char *s, t_cs sc, int fd)
{
	int	len;
	int	pad;

	if (s == NULL)
		s = "(null)";
	len = ft_strlen(s);
	if (sc.precision >= 0 && len > sc.precision)
		len = sc.precision;
	pad = 0;
	print_padding(1, sc, &pad, len);
	ft_putstr_limit_fd(s, len, fd);
	print_padding(0, sc, &pad, len);
	return (len + pad);
}
