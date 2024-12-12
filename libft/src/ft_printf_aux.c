/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:58:15 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:18 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * deals padding ("-w" flags)
*/
void	print_padding(int left, t_cs sc, int *pad, int len)
{
	if (left)
	{
		if (sc.min_width_lpad > 0 && sc.min_width_lpad > len)
			*pad = sc.min_width_lpad - len;
		if (*pad > 0 && !sc.minus_rpad)
			ft_putchar_times_fd(' ', *pad, 1);
	}
	else
	{
		if (*pad > 0 && sc.minus_rpad)
			ft_putchar_times_fd(' ', *pad, 1);
	}
}

/**
 * deals with number flags: "0w.prec".
 * it updates _len_ (length of the raw number with sign and no left zeros)
 * and returns _lzeros_ (number of '0' chars at the left) 
*/
int	process_numflags(char *str, char sign,
	t_cs sc, int *len)
{
	int	lzeros;

	lzeros = 0;
	*len = ft_strlen(str);
	if (sc.precision > 0 && sc.precision > *len)
		lzeros = sc.precision - *len;
	*len = *len + (int)(sign != '\0');
	if (sc.zero_lpad && !sc.minus_rpad && sc.precision < 0
		&& sc.min_width_lpad > 0 && sc.min_width_lpad > *len)
		lzeros = sc.min_width_lpad - *len;
	if (lzeros == 0)
		sc.zero_lpad = 0;
	return (lzeros);
}
