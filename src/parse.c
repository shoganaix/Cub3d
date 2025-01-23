/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:27:48 by msoriano          #+#    #+#             */
/*   Updated: 2025/01/23 16:42:04 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool can_open (const char *file_name)
{
	int			fdin;

	fdin = open(file_name, O_RDONLY);
	if (fdin < 0)
		return (my_perror("Error: input file error at open"), FALSE);
	close(fdin);
	return TRUE;
}

t_bool check_fmt_extension(const char *file_name, char *ext_w_dot)
{
	int     diff;

	if (!ft_strrchr(file_name, '.'))
		return FALSE;
	diff = ft_strncmp(ft_strrchr(file_name, '.'),
		ext_w_dot, ft_strlen(ext_w_dot) + 1);
	return (diff == 0);
}
/**
 * - num args
 * - extension
 * - file existence, can be read
 */
t_bool check_args(int argn, char *args[])
{
	if (argn != 2)
		return FALSE;
	if (!check_fmt_extension(args[1], ".cub"))
		return FALSE;
	if (!can_open(args[1]))
		return FALSE;
	return TRUE;
}

