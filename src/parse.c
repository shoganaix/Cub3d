/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:27:48 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/17 22:58:52 by msoriano         ###   ########.fr       */
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
void	check_args(int argn, char *args[])
{
	t_errcode	e;

	e = ERR_OK;
	if (argn != 2)
		e = ERR_ARGNUM;
	else if (!check_fmt_extension(args[1], ".cub"))
		e = ERR_ARGFORMAT;
	else if (!can_open(args[1]))
		e = ERR_ARGNOTFOUND;
	if (e != ERR_OK)
		my_perrorcode_exit(e, NULL);
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
