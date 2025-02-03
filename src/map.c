/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:39:12 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/03 13:05:39 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

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


t_bool color_val_ok(char *s, int *v)
{
	if (!s) 
		return (FALSE);
	if (ft_atoi_secure(s, v) && *v >= 0 && *v <= 255)
		return (TRUE);
	return (FALSE);
}

t_bool	check_color(char *line, t_info *info, char *item)
{
	debug_str("-- check_color", item);
	char	*first;
	int		i;
	char **strs;
	t_color	*color;

	if (ft_strcmp(item, "C") == 0)
		color = &info->ceiling;
	if (ft_strcmp(item, "F") == 0)
		color = &info->floor;
	i = 0;
	first = next_word(line, &i);
	if (ft_strcmp(first, item) != 0)
		return (debug("wrong code"), free(first), FALSE);
	free(first);
	while (is_space(line[i]))
		i++;
	if (line[i])
	{
		if (color->r != -1)
			return (debug("already filled"), FALSE);
		strs = ft_split(&line[i], ',');
		if (!(color_val_ok(strs[0], &color->r) 
			&& color_val_ok(strs[1], &color->g)
			&& color_val_ok(strs[2], &color->b)))
			return (debug("bad format color"), ft_free_arrstr(strs), FALSE);
		if (strs[3])
			return (debug("more than needed"), ft_free_arrstr(strs), FALSE);
		return (ft_free_arrstr(strs), TRUE);
	}
	debug("no color given for the code");
	return (FALSE);
}

t_errcode check_line(char *line, t_info *info)
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
	if (check_color(line, info, "C"))
		return (ERR_OK);
	if (check_color(line, info, "F"))
		return (ERR_OK);
	debug("wrong input");
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

t_errcode check_map(char *cubfile, t_info *info)
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