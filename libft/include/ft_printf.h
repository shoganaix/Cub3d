/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:25:22 by macastro          #+#    #+#             */
/*   Updated: 2023/11/30 19:11:00 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

# define FLAG		"-+#0 *.0123456789"
# define SPECS		"cspdiuxX%"
# define HEXMAY		"0123456789ABCDEF"
# define HEXMIN 	"0123456789abcdef"

/**
 * Behavior %"-0# +W.prec"specifier
 * -----------------
 * w	: left padding with ' 's (pad "--s")
 * 0w	: left padding, '0' for numbers diuxX, indefined for other conversions
 * -w	: right padding with ' 's (pad "s--")
 * .precision : nothing -> 1, .-> 0, 
 * 		the min number of digits to appear for diuxX (0)
 * 		the max number of chars to be printed for s. (' ')
 * 		When 0 is printed with an explicit precision 0, the output is empty.
 * -0 : 0 < -
 * 0.prec : 0 < .prec
 * -.prec : -w + .prec
 * -0.prec : (0) < (-w + .prec)
 * w.prec : w + .prec
 * %%
 * # alt form: x-> 0x pref, -> 0X pref, cdipsu no effect
 * ' ' (space) : blank before positive number (d,i)
 * + sign always: + for pos, - for neg (d,i)
 * + > ' '

*/
typedef struct s_conv_specif
{
	int		minus_rpad;
	int		zero_lpad;
	int		hash_alt_form;
	int		space_positive;
	int		plus_positive;
	int		min_width_lpad;
	int		precision;
	char	sp;
}	t_cs;

#endif
