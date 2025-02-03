/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:02:57 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/03 13:46:27 by msoriano         ###   ########.fr       */
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
