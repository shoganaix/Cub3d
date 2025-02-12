/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:10:36 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/12 16:59:17 by macastro         ###   ########.fr       */
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
	const char	*err_msg[NUM_ERR] = {
		"Success",
		"Error: wrong number of args. Expected 1: a cub file.",
		"Error: file not found or not enough permissions.",
		"Error: argument must be a cub file.",
		"Error: not valid format in cub info.",
		"Error: info is missing in cub file.",
		"Error: info is dupped in cub file.",
		"Error: invalid character in map.",
		"Error: invalid space character in map.",
		"Error: player not found in map.",
		"Error: map not closed.",

		"Error: memory failed."
	};

	if (err >= 0 && err < NUM_ERR)
		my_perror((char *)err_msg[err]);
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
