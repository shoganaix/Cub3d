/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:18:11 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/17 22:41:16 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// map???
void	init_cub(t_cub *cub)
{
	init_info(&cub->info);
	cub->smap.map = ft_calloc(1, sizeof(char *));
	if (cub->smap.map == NULL)
	{
		destroy_info(&cub->info);
		my_perrorcode_exit(ERR_MEM, NULL);
	}
	cub->smap.height = 0;
	cub->smap.width = 0;
	cub->smap.player_pos[0] = -1;
	cub->smap.player_pos[1] = -1;
	cub->smap.player_or = NO;
}

void	destroy_cub(t_cub *cub)
{
	destroy_info(&cub->info);
	ft_free_arrstr(cub->smap.map);
}

static void	save_mapline(t_cub *cub, char *line)
{
	char	**map_tmp;
	int		i;

	if (!line)
		return ;
	cub->smap.width = ft_max_nbr(cub->smap.width, ft_strlen(line));
	cub->smap.height++;
	map_tmp = (char **)ft_calloc((cub->smap.height + 1), sizeof(char *));
	if (map_tmp == NULL)
		(destroy_cub(cub), my_perrorcode_exit(ERR_MEM, "map_temp failed"));
	i = 0;
	while (i < cub->smap.height - 1)
	{
		map_tmp[i] = cub->smap.map[i];
		i++;
	}
	map_tmp[i] = ft_strdup(line);
	if (map_tmp[i] == NULL)
	{
		free(map_tmp);
		destroy_cub(cub);
		my_perrorcode_exit(ERR_MEM, "map_temp row creation failed");
	}
	free(cub->smap.map);
	cub->smap.map = map_tmp;
}

static void	eat_newlines(int fd_in, char **line)
{
	while (*line && ft_strcmp(*line, "\n") == 0)
	{
		free(*line);
		*line = get_next_line(fd_in);
	}
}

/**
 * reads info and map
 * performs several checks
 */
t_errcode	read_cubfile(char *cubfile, t_cub *cub)
{
	t_errcode	e;
	int			fdin;
	char		*line;

	init_cub(cub);
	fdin = open(cubfile, O_RDONLY);
	if (fdin == -1)
		return (ERR_ARGNOTFOUND);
	line = get_next_line(fdin);
	e = check_cub_info(fdin, &cub->info, &line);
	if (e != ERR_OK)
		return (close(fdin), e);
	eat_newlines(fdin, &line);
	while (line)
	{
		save_mapline(cub, line);
		free(line);
		line = get_next_line(fdin);
	}
	close(fdin);
	e = check_map_invalid_chars(cub);
	if (e == ERR_OK)
		e = check_map_closed(cub);
	return (e);
}
