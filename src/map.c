/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:39:12 by msoriano          #+#    #+#             */
/*   Updated: 2025/01/23 19:00:22 by msoriano         ###   ########.fr       */
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


t_bool	check_color(char *line, t_info *info, char *item)
{
	char	*first;
	int		i;
	char **strs;
	int j;

	// i = 0;
	// first = next_word(line, &i);
	// if (ft_strcmp(first, item) != 0)
	// 	return (free(first), FALSE);
	// free(first);
	// while (is_space(line[i]))
	// 	i++;
	// if (line[i])
	// {
	// 	strs = ft_split(&line[i], ',');
	// 	j = 0;
	// 	ft_atoi(strs[j]);


	// }
}


t_bool check_line(char *line, t_info *info)
{
	if (check_texture(line, info, "NO", NO))
		return TRUE;
	if (check_texture(line, info, "SO", SO))
		return TRUE;
	if (check_texture(line, info, "WE", WE))
		return TRUE;
	if (check_texture(line, info, "EA", EA))
		return TRUE;
	// check colors
	return FALSE;
}

//t_bool check_map_info()

t_bool check_map(char *cubfile, t_info *info)
{
	int		fdin;
	char	*line;
	t_bool	is_complete;

	fdin = open(cubfile, O_RDONLY);
	init_info(info);
	is_complete = FALSE;

	line = get_next_line(fdin);
	while (line && !is_complete)
	{
		if (ft_strcmp(line, "") == 0)
			continue ;
		if (!check_line(line, info))
			return (FALSE);
		is_complete = ((info->textures[NO] != NULL)
				&& (info->textures[SO] != NULL)
				&& (info->textures[WE] != NULL)
				&& (info->textures[EA] != NULL)
				&& (info->ceiling.r != -1)
				&& (info->floor.r != -1));
	}

	return TRUE;
}