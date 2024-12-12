/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_csp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:56:02 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:19 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void	init_conversion_specification(t_cs *cs)
{
	if (!cs)
		cs = (t_cs *)malloc(sizeof(t_cs *));
	cs->precision = -1;
	cs->min_width_lpad = 0;
	cs->minus_rpad = 0;
	cs->zero_lpad = 0;
	cs->hash_alt_form = 0;
	cs->space_positive = 0;
	cs->plus_positive = 0;
	cs->sp = '\0';
}

static int	atoi_and_advance(const char *str, int *i)
{
	int	n;

	n = ft_atoi(&str[*i]);
	while (ft_strchr("0123456789", str[*i]))
		*i += 1;
	return (n);
}

static void	build_conversion_specification(const char *format, int *i,
	t_cs *cs)
{
	while (format[*i] && ft_strchr("-0# +", format[*i]))
	{
		cs->minus_rpad = cs->minus_rpad || (format[*i] == '-');
		cs->zero_lpad = cs->zero_lpad || (format[*i] == '0');
		cs->hash_alt_form = cs->hash_alt_form || (format[*i] == '#');
		cs->space_positive = cs->space_positive || (format[*i] == ' ');
		cs->plus_positive = cs->plus_positive || (format[*i] == '+');
		*i += 1;
	}
	cs->min_width_lpad = atoi_and_advance(format, i);
	if (format[*i] == '.')
	{
		*i += 1;
		cs->precision = atoi_and_advance(format, i);
	}
	cs->sp = format[*i];
	*i += 1;
}

t_cs	*read_csp(const char *str, int *i)
{
	t_cs	*csp;

	csp = ft_calloc(1, sizeof(t_cs));
	if (!csp)
		return (NULL);
	init_conversion_specification(csp);
	build_conversion_specification(str, i, csp);
	return (csp);
}
