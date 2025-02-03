/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:10:36 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/03 13:24:01 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_perr_arg(char *msg, char *var_name)
{
	write(2, msg, ft_strlen(msg));
	write(2, ": ", 2);
	write(2, var_name, ft_strlen(var_name));
	write(2, "\n", 1);
}

void	my_perr_arg_exit(char *msg, char *var_name)
{
	write(2, msg, ft_strlen(msg));
	write(2, ": ", 2);
	write(2, var_name, ft_strlen(var_name));
	write(2, "\n", 1);
	exit(1);
}
