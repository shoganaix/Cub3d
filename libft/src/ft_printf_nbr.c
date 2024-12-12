/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:03:40 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:20 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	get_sign_char(long n, t_cs cs)
{
	char	sign;

	sign = '\0';
	if (n < 0)
		sign = '-';
	else if (n >= 0 && cs.plus_positive)
		sign = '+';
	else if (n >= 0 && cs.space_positive)
		sign = ' ';
	return (sign);
}

/**
 * Given an unsigned int, it returns it as a string
 * (no sign or left zeros added)
*/
static char	*get_unum_as_str(unsigned int unsigned_num, t_cs sc)
{
	char	*str;

	if (sc.sp == 'x' || sc.sp == 'X')
		str = number_to_strhex(unsigned_num, (int)(sc.sp == 'X'));
	else
		str = number_to_strdec(unsigned_num);
	if (sc.precision == 0 && unsigned_num == 0)
	{
		free(str);
		str = ft_calloc(1, 1);
		if (!str)
			return (NULL);
	}
	return (str);
}

/**
 * For %i and %d.
 * // si prec --> prec, sign, -w
 * // si !prec && minus -> sign, -w
 * // si !prec && !minus && zero --> sign, 0 (%03d, -2 : "-02")	
 * Possible flags: "-0 +w.prec": prec, sign (' '+) NUM, -0w
*/
int	print_signed_number(long number, t_cs sc, int fd)
{
	char	*str;
	char	sign;
	int		len;
	int		lzeros;
	int		pad;

	sign = get_sign_char(number, sc);
	if (number < 0)
		number = -1 * number;
	str = get_unum_as_str(number, sc);
	lzeros = process_numflags(str, sign, sc, &len);
	len = lzeros + len;
	pad = 0;
	print_padding(1, sc, &pad, len);
	if (sign)
		ft_putchar_fd(sign, fd);
	ft_putchar_times_fd('0', lzeros, fd);
	ft_putstr_fd(str, fd);
	print_padding(0, sc, &pad, len);
	free(str);
	return (len + pad);
}

/**
 * For %u.
 * Possible flags: "-0w.prec": prec, NUM, -0w
*/
int	print_unsigned_number(unsigned int number, t_cs sc)
{
	char	*str;
	int		len;
	int		lzeros;
	int		pad;

	str = get_unum_as_str(number, sc);
	lzeros = process_numflags(str, '\0', sc, &len);
	len = lzeros + len;
	pad = 0;
	print_padding(1, sc, &pad, len);
	ft_putchar_times_fd('0', lzeros, 1);
	ft_putstr_fd(str, 1);
	print_padding(0, sc, &pad, len);
	free(str);
	return (len + pad);
}

/**
 * For %x %X.
 * Possible flags: "-0#w.prec": prec, #NUM, -0w
*/
int	print_unsigned_hex(unsigned int number, t_cs csp)
{
	char	*str;
	int		len;
	int		lzeros;
	int		pad;

	str = get_unum_as_str(number, csp);
	lzeros = process_numflags(str, '\0', csp, &len);
	if (csp.precision < 0 && csp.zero_lpad
		&& csp.hash_alt_form && number != 0)
		lzeros = ft_min_nbr(lzeros - 2, 0);
	len = lzeros + len + 2 * (csp.hash_alt_form && number != 0);
	pad = 0;
	print_padding(1, csp, &pad, len);
	if (csp.hash_alt_form && number != 0)
	{
		ft_putchar_fd('0', 1);
		ft_putchar_fd(csp.sp, 1);
	}
	ft_putchar_times_fd('0', lzeros, 1);
	ft_putstr_fd(str, 1);
	print_padding(0, csp, &pad, len);
	free(str);
	return (len + pad);
}
