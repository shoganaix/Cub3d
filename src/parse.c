/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:27:48 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/03 13:42:46 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	can_open(const char *file_name)
{
	int			fdin;

	fdin = open(file_name, O_RDONLY);
	if (fdin < 0)
		return (FALSE);
	close(fdin);
	return (TRUE);
}

t_bool	check_fmt_extension(const char *file_name, char *ext_w_dot)
{
	int	diff;

	if (!ft_strrchr(file_name, '.'))
		return (FALSE);
	diff = ft_strncmp(ft_strrchr(file_name, '.'),
			ext_w_dot, ft_strlen(ext_w_dot) + 1);
	return (diff == 0);
}

/**
 * - num args
 * - extension
 * - file existence, can be read
 */
t_errcode	check_args(int argn, char *args[])
{
	if (argn != 2)
		return (ERR_ARGNUM);
	if (!check_fmt_extension(args[1], ".cub"))
		return (ERR_ARGFORMAT);
	if (!can_open(args[1]))
		return (ERR_ARGNOTFOUND);
	return (ERR_OK);
}

t_bool	color_val_ok(char *s, int *v)
{
	if (!s)
		return (FALSE);
	if (ft_atoi_secure(s, v) && *v >= 0 && *v <= 255)
		return (TRUE);
	return (FALSE);
}

char	*next_word(char *line, int *len)
{
	char	*w;

	if (!ft_strchri(line, ' '))
		w = ft_strdup(line);
	else
		w = ft_substr(line, 0, ft_strchri(line, ' '));
	*len += ft_strlen(w);
	return (w);
}
