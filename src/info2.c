/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:12:17 by macastro          #+#    #+#             */
/*   Updated: 2025/02/19 16:23:59 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_errcode	check_texture(char *line, t_info *info, t_card cp)
{
	char	*first;
	int		i;

	i = 0;
	first = next_word(line, &i);
	if (ft_strcmp(first, cardinal_to_str(cp)) == 0)
	{
		free(first);
		while (is_space(line[i]))
			i++;
		if (line[i])
		{
			if (info->tx_paths[cp] != NULL)
				return (ERR_CUBINFODUPPED);
			info->tx_paths[cp] = next_word(&line[i], &i);
		}
		if (line[i] || info->tx_paths[cp] == NULL)
			return (ERR_CUBINFOFORMAT);
		return (ERR_OK);
	}
	free(first);
	return (ERR_CUBINFOFORMAT);
}

t_errcode	check_color(char *line, char *item, t_color *color)
{
	char	*first;
	int		i;
	char	**strs;

	i = 0;
	first = next_word(line, &i);
	if (ft_strcmp(first, item) != 0)
		return (free(first), ERR_CUBINFOFORMAT);
	free(first);
	while (is_space(line[i]))
		i++;
	if (line[i])
	{
		if (color->r != -1)
			return (ERR_CUBINFODUPPED);
		strs = ft_split(&line[i], ',');
		if (!(color_val_ok(strs[0], &color->r)
				&& color_val_ok(strs[1], &color->g)
				&& color_val_ok(strs[2], &color->b)))
			return (ft_free_arrstr(strs), ERR_CUBINFOFORMAT);
		if (strs[3])
			return (ft_free_arrstr(strs), ERR_CUBINFOFORMAT);
		return (ft_free_arrstr(strs), ERR_OK);
	}
	return (ERR_CUBINFOFORMAT);
}

/**
 * check if a texture line or color line is read.
 * Otherwise, format error
 */
t_errcode	check_infoline(char *line, t_info *info)
{
	t_errcode	e;
	t_card		cp;

	line = ft_strtrim(line, "\n");
	cp = 0;
	while (cp < NUM_CARD)
	{
		e = check_texture(line, info, cp);
		if (e != ERR_CUBINFOFORMAT)
			return (e);
		cp++;
	}
	e = check_color(line, "C", &info->ceiling);
	if (e != ERR_CUBINFOFORMAT)
		return (e);
	e = check_color(line, "F", &info->floor);
	if (e != ERR_CUBINFOFORMAT)
		return (e);
	return (ERR_CUBINFOFORMAT);
}

void	finish_gnl(int fd_in, char **line)
{
	while (*line)
	{
		free(*line);
		*line = get_next_line(fd_in);
	}
}

t_errcode	check_cub_info(int fd_in, t_info *info, char **line)
{
	t_bool		is_complete;
	t_errcode	e;

	is_complete = FALSE;
	e = ERR_OK;
	while (*line && !is_complete)
	{
		if (ft_strcmp(*line, "\n") != 0)
		{
			e = check_infoline(*line, info);
			if (e != ERR_OK)
				return (my_perr_arg("error in line", *line), e);
			is_complete = ((info->tx_paths[NO] != NULL)
					&& (info->tx_paths[SO] != NULL)
					&& (info->tx_paths[WE] != NULL)
					&& (info->tx_paths[EA] != NULL)
					&& (info->ceiling.r != -1)
					&& (info->floor.r != -1));
		}
		free(*line);
		*line = get_next_line(fd_in);
	}
	if (!is_complete)
		return (ERR_CUBINFOMISSING);
	return (e);
}
