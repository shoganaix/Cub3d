/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:18:11 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/12 16:46:25 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_errcode	check_cub_map_row(t_cub *cub, int r, t_bool *player_found)
{
	char	last;
	int		c;

	c = 0;
	last = '\0';
	while (c < cub->smap.width && cub->smap.map[r][c] != '\n')
	{
		if (ft_strchr("01 ", cub->smap.map[r][c]) == NULL)
		{
			if (!(*player_found) && ft_strchr("NSEW", cub->smap.map[r][c]))
			{
				*player_found = TRUE;
				cub->smap.player_pos[0] = r;
				cub->smap.player_pos[1] = c;
				cub->smap.player_or = cub->smap.map[r][c];
			}
			else
				return (destroy_cub(cub), ERR_CUBINVALID);
		}
		if ((cub->smap.map[r][c] == ' ')
				&& !(!last || last == ' ' || last == '1'))
			return (destroy_cub(cub), ERR_CUBINVALIDSPC);
		last = cub->smap.map[r][c++];
	}
	return (ERR_OK);
}

/**
 * Check if there are invalid characters:
 * - valid: space, 1, 0, player char
 * - player char appears only once
 * - no horizontal spaces in between maps content
 * Saves player position and orientation
 */
t_errcode	check_invalid_chars(t_cub *cub)
{
	int			r;
	t_bool		player_found;
	t_errcode	e;

	player_found = FALSE;
	r = 0;
	while (r < cub->smap.height)
	{
		e = check_cub_map_row(cub, r, &player_found);
		if (e != ERR_OK)
			return (e);
		r++;
	}
	if (!player_found)
		return (ERR_PLAYERNOTFOUND);
	return (ERR_OK);
}

/**
 * if flood == 0 -> the map is closed
 * if flood > 0 -> flood overflows
 * 
 * The first call must be inside.
 * cases:
 * - out of the map -> overflow
 * - is wall or already seen -> end recursion
 * - is not valid terrain ('0') -> overflow
 * - is valid terrain -> mark as seen + explore 4 directions (recursion)
 */
int	apply_flood_fill(char **map_copy, int i, int j, char filled)
{
	if (i < 0 || j < 0
		|| map_copy[i] == NULL
		|| j > (int) ft_strlen(map_copy[i])
		|| map_copy[i][j] == '\n' || map_copy[i][j] == '\0'
		)
		return (1);
	else if (map_copy[i][j] == '1' || map_copy[i][j] == filled)
		return (0);
	else if (map_copy[i][j] != '0')
		return (1);
	map_copy[i][j] = filled;
	return (
		apply_flood_fill(map_copy, i, j - 1, filled)
		+ apply_flood_fill(map_copy, i - 1, j, filled)
		+ apply_flood_fill(map_copy, i, j + 1, filled)
		+ apply_flood_fill(map_copy, i + 1, j, filled)
	);
}

char	**copy_map_arr(t_map m)
{
	char	**map_copy;
	int		i;
	int		j;

	map_copy = (char **)ft_calloc((m.height + 1), sizeof(char *));
	if (map_copy == NULL)
		return (NULL);
	i = 0;
	while (i < m.height)
	{
		j = 0;
		map_copy[i] = (char *)ft_calloc(ft_strlen(m.map[i]) + 1, sizeof(char));
		if (map_copy[i] == NULL)
			return (ft_free_arrstr(map_copy), NULL);
		while (m.map[i][j] != '\0')
		{
			map_copy[i][j] = m.map[i][j];
			j++;
		}
		i++;
	}
	return (map_copy);
}

// create copy to explore
// algo
t_errcode	check_cub_closed(t_cub *cub)
{
	char	**map_copy;
	int		flood;

	map_copy = copy_map_arr(cub->smap);
	if (map_copy == NULL)
		return (destroy_cub(cub), ERR_MEM);
	map_copy[cub->smap.player_pos[0]][cub->smap.player_pos[1]] = '0';
	flood = apply_flood_fill(map_copy, cub->smap.player_pos[0],
			cub->smap.player_pos[1], cub->smap.player_or);
	debug_int("flood", flood);
	ft_putarr_str(map_copy);
	debug_int("flood", flood);
	if (flood > 0)
		return (destroy_cub(cub), ERR_CUBNOTCLOSED);
	return (ERR_OK);
}

void	save_mapline(t_cub *cub, char *line)
{
	char	**map_tmp;
	int		i;

	if (!line)
		return ;
	cub->smap.width = ft_max_nbr(cub->smap.width, ft_strlen(line));
	cub->smap.height++;
	map_tmp = (char **)ft_calloc((cub->smap.height + 1), sizeof(char *));
	if (map_tmp == NULL)
	{
		destroy_cub(cub);
		my_perrorcode_exit(ERR_MEM, NULL);
	}
	i = 0;
	while (i < cub->smap.height - 1)
	{
		map_tmp[i] = cub->smap.map[i];
		i++;
	}
	map_tmp[i] = ft_strdup(line);
	if (cub->smap.map[0])
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

t_errcode	check_cubfile(char *cubfile, t_cub *cub)
{
	int			fdin;
	char		*line;
	t_errcode	e;

	init_cub(cub);
	fdin = open(cubfile, O_RDONLY);
	if (fdin == -1)
		return (ERR_ARGNOTFOUND);
	line = get_next_line(fdin);
	e = check_cub_info(fdin, &cub->info, &line);
	if (e != ERR_OK)
		return (e);
	eat_newlines(fdin, &line);
	while (line)
	{
		save_mapline(cub, line);
		free(line);
		line = get_next_line(fdin);
	}
	close(fdin);
	e = check_invalid_chars(cub);
	if (e == ERR_OK)
		e = check_cub_closed(cub);
	return (e);
}
