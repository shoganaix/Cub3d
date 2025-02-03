/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:10:36 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/03 13:15:01 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_perror(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	my_perror_exit(char *msg)
{
	my_perror(msg);
	exit(1);
}

void	my_perrorcode(t_errcode err, char *msg)
{
	if (err == ERR_ARGNUM)
		my_perror("Error: wrong number of arguments. Expected 1.");
	else if (err == ERR_ARGFORMAT)
		my_perror("Error: argument must be a cub file.");
	else if (err == ERR_ARGNOTFOUND)
		my_perror("Error: file not found. Check permissions.");

	else if (err == ERR_CUBINFOFORMAT)
		my_perror("Error: not valid format in cub info.");
	else if (err == ERR_CUBINFOMISSING)
		my_perror("Error: info is missing in cub file.");
	else if (err == ERR_CUBINFODUPPED)
		my_perror("Error: info is dupped in cub file.");
	if (msg != NULL)
		my_perror(msg);
}

void	my_perrorcode_exit(t_errcode err, char *msg)
{
	my_perrorcode(err, msg);
	exit(1);
}

void	my_perror_exit_st(char *msg, int err)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(err);
}

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