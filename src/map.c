/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:39:12 by msoriano          #+#    #+#             */
/*   Updated: 2025/01/24 20:07:42 by macastro         ###   ########.fr       */
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

t_bool	check_texture(char *line, t_info *info, char *texture, t_card cp)
{
	char	*first;
	int		i;

	i = 0;
	first = next_word(line, &i);
	if (ft_strcmp(first, texture) == 0)
	{
		free(first);
		while (is_space(line[i]))
			i++;
		if (line[i])
		{
			if (info->textures[cp] != NULL)
				return (FALSE);
			info->textures[cp] = next_word(&line[i], &i);
		}
		if (line[i])
			return (FALSE);
		return (info->textures[cp] != NULL);
	}
	free(first);
	return (FALSE);
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
		return (free(first), FALSE);
	free(first);
	while (is_space(line[i]))
		i++;
	if (line[i])
	{
		if (color->r != -1)
			return (FALSE);
		strs = ft_split(&line[i], ',');
		
		if (!(color_val_ok(strs[0], &color->r) 
			&& color_val_ok(strs[1], &color->g)
			&& color_val_ok(strs[2], &color->b)))
			return (ft_free_arrstr(strs), FALSE);
		if (strs[3])
			return (ft_free_arrstr(strs), FALSE);
		return (ft_free_arrstr(strs), TRUE);
	}
	return (FALSE);

}


t_bool check_line(char *line, t_info *info)
{
	line = ft_strtrim(line, "\n");
	if (check_texture(line, info, "NO", NO))
		return TRUE;
	if (check_texture(line, info, "SO", SO))
		return TRUE;
	if (check_texture(line, info, "WE", WE))
		return TRUE;
	if (check_texture(line, info, "EA", EA))
		return TRUE;
	if (check_color(line, info, "C"))
		return TRUE;
	if (check_color(line, info, "F"))
		return TRUE;
	return FALSE;
}

//t_bool check_map_info()

t_bool check_map(char *cubfile, t_info *info)
{
	int		fdin;
	char	*line;
	t_bool	is_complete;

	fdin = open(cubfile, O_RDONLY);
	if (fdin == -1)
		my_perror_exit("Error. File not found or allowed.");
	init_info(info);
	is_complete = FALSE;
	line = get_next_line(fdin);
	while (line && !is_complete)
	{
		if (ft_strcmp(line, "\n") != 0)
		{
			if (!check_line(line, info))
				return (FALSE);
			is_complete = ((info->textures[NO] != NULL)
					&& (info->textures[SO] != NULL)
					&& (info->textures[WE] != NULL)
					&& (info->textures[EA] != NULL)
					&& (info->ceiling.r != -1)
					&& (info->floor.r != -1));
		}
		free(line);
		line = get_next_line(fdin);
	}
	return (is_complete);
}