/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:10:36 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/11 14:42:03 by macastro         ###   ########.fr       */
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
		my_perror("Error: wrong number of args. Expected 1: a cub file.");
	else if (err == ERR_ARGFORMAT)
		my_perror("Error: argument must be a cub file.");
	else if (err == ERR_ARGNOTFOUND)
		my_perror("Error: file not found or not enough permissions.");
	else if (err == ERR_CUBINFOFORMAT)
		my_perror("Error: not valid format in cub info.");
	else if (err == ERR_CUBINFOMISSING)
		my_perror("Error: info is missing in cub file.");
	else if (err == ERR_CUBINFODUPPED)
		my_perror("Error: info is dupped in cub file.");
	else if (err == ERR_MEM)
		my_perror("Error: memory failed.");
	else if (err == ERR_CUBINVALID)
		my_perror("Error: invalid character in map.");
	else if (err == ERR_CUBINVALIDSPC)
		my_perror("Error: invalid space character in map.");
	else if (err == ERR_PLAYERNOTFOUND)
		my_perror("Error: player not found in map.");
	else
		my_perror("Error: unknown.");
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
