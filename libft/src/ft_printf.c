/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:35:45 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:22 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	print_value(va_list ap, t_cs csp)
{
	if (csp.sp == 'c')
		return (print_char(va_arg(ap, int), csp, 1));
	if (csp.sp == 's')
		return (print_str(va_arg(ap, char *), csp, 1));
	if (csp.sp == 'p')
		return (print_pointer(va_arg(ap, void *), csp));
	if (csp.sp == 'd' || csp.sp == 'i')
		return (print_signed_number(va_arg(ap, int), csp, 1));
	if (csp.sp == 'u')
		return (print_unsigned_number(va_arg(ap, unsigned int), csp));
	if (csp.sp == 'x' || csp.sp == 'X')
		return (print_unsigned_hex(va_arg(ap, unsigned int), csp));
	if (csp.sp == '%')
		return (print_char('%', csp, 1));
	return (0);
}

static int	print_specifier(const char *format, va_list args, int *i)
{
	t_cs	*csp;
	int		printed_len;

	csp = read_csp(format, i);
	if (!csp)
		return (-1);
	printed_len = print_value(args, *csp);
	free(csp);
	return (printed_len);
}

/**
 * Prints as in printf
 * 
 * Available conversions: cspdiuxX%
 * Each conversion especification has:
 * start: %
 * in between: ("-0# +w.prec")
 * - none or more flags ("-0# +")
 * - optional minimum field width
 * - optional precision (.)
 * end: a conversion specifier (cspdiuxX %)
 * 
*/
int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		total_len;
	int		i;
	int		cur_len;

	total_len = 0;
	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] != '%')
		{
			ft_putchar_fd(format[i++], 1);
			total_len++;
			continue ;
		}
		i++;
		cur_len = print_specifier(format, ap, &i);
		if (cur_len < 0)
			return (-1);
		total_len = total_len + cur_len;
	}
	va_end(ap);
	return (total_len);
}
