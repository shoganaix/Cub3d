/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:02:57 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/11 14:15:03 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug(char *msg)
{
	if (!DEBUG)
		return ;
	ft_putstr_fd(ANSI_COLOR_YELLOW "", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	ft_putstr_fd("" ANSI_COLOR_RESET, 2);
}

void	debug_int(char *name_desc, int n)
{
	if (!DEBUG)
		return ;
	ft_putstr_fd(ANSI_COLOR_YELLOW "", 2);
	write(2, name_desc, ft_strlen(name_desc));
	write(2, " ", 1);
	ft_putnbr_fd(n, 2);
	write(2, "\n", 1);
	ft_putstr_fd("" ANSI_COLOR_RESET, 2);
}

void	debug_str(char *name_desc, char *str)
{
	if (!DEBUG)
		return ;
	ft_putstr_fd(ANSI_COLOR_YELLOW "", 2);
	write(2, name_desc, ft_strlen(name_desc));
	write(2, " [", 2);
	ft_putstr_fd(str, 2);
	write(2, "]\n", 2);
	ft_putstr_fd("" ANSI_COLOR_RESET, 2);
}

void	debug_chr(char *name_desc, char c)
{
	if (!DEBUG)
		return ;
	ft_putstr_fd(ANSI_COLOR_YELLOW "", 2);
	write(2, name_desc, ft_strlen(name_desc));
	write(2, " [", 2);
	ft_putchar_fd(c, 2);
	write(2, "]\n", 2);
	ft_putstr_fd("" ANSI_COLOR_RESET, 2);
}
