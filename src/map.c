/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:39:12 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/03 15:07:36 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_errcode	check_texture(char *line, t_info *info, t_card cp)
{
	char	*first;
	int		i;

	i = 0;
	first = next_word(line, &i);
	if (ft_strcmp(first, cardinal_tostr(cp)) == 0)
	{
		free(first);
		while (is_space(line[i]))
			i++;
		if (line[i])
		{
			if (info->textures[cp] != NULL)
				return (ERR_CUBINFODUPPED);
			info->textures[cp] = next_word(&line[i], &i);
		}
		if (line[i] || info->textures[cp] == NULL)
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

t_errcode	check_line(char *line, t_info *info)
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

t_errcode	check_map_info(int fd_in, t_info *info, char **line)
{
	t_bool		is_complete;
	t_errcode	e;

	is_complete = FALSE;
	e = ERR_OK;
	while (*line && !is_complete)
	{
		if (ft_strcmp(*line, "\n") != 0)
		{
			e = check_line(*line, info);
			if (e != ERR_OK)
				return (e);
			is_complete = ((info->textures[NO] != NULL)
					&& (info->textures[SO] != NULL)
					&& (info->textures[WE] != NULL)
					&& (info->textures[EA] != NULL)
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

t_errcode	check_map(char *cubfile, t_info *info)
{
	int		fdin;
	char	*line;
	t_errcode e;

	init_info(info);
	fdin = open(cubfile, O_RDONLY);
	if (fdin == -1)
		return (ERR_ARGNOTFOUND);
	line = get_next_line(fdin);
	e = check_map_info(fdin, info, &line);
	while (line)
	{
		free(line);
		line = NULL;
		line = get_next_line(fdin);
	}
	close(fdin);
	return (e);
}