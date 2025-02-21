/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:39:12 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/21 19:52:25 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_errcode	check_map_row(t_cub *cub, int r, t_bool *player_found)
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
				cub->smap.player_or = char_to_cardinal(cub->smap.map[r][c]);
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
t_errcode	check_map_invalid_chars(t_cub *cub)
{
	int			r;
	t_bool		player_found;
	t_errcode	e;

	player_found = FALSE;
	r = 0;
	while (r < cub->smap.height)
	{
		e = check_map_row(cub, r, &player_found);
		if (e != ERR_OK)
			return (e);
		r++;
	}
	if (!player_found)
		return (ERR_PLAYERNOTFOUND);
	return (ERR_OK);
}

t_bool	is_inside_grid(char **grid, int r, int c, int grid_nrows)
{
	//ft_printf("is_inside_grid - r:%i C:%i\n", r, c);
	if (r < 0 || c < 0 || r > grid_nrows - 1
		|| grid[r] == NULL
		|| c > (int) ft_strlen(grid[r])
		|| grid[r][c] == '\n' || grid[r][c] == '\0'
		)
		return (FALSE);
	else
		return (TRUE);
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
static int	apply_flood_fill(char **map_copy, int i, int j, int map_height)
{
	const char	filled = 'X';

	if (i < 0 || j < 0 || i > map_height - 1
		|| map_copy[i] == NULL
		|| j > (int) ft_strlen(map_copy[i])
		|| map_copy[i][j] == '\n' || map_copy[i][j] == '\0' // todo
		)
		return (1);
	else if (map_copy[i][j] == '1' || map_copy[i][j] == filled)
		return (0);
	else if (map_copy[i][j] != '0')
		return (1);
	map_copy[i][j] = filled;
	return (apply_flood_fill(map_copy, i, j - 1, map_height)
		+ apply_flood_fill(map_copy, i - 1, j, map_height)
		+ apply_flood_fill(map_copy, i, j + 1, map_height)
		+ apply_flood_fill(map_copy, i + 1, j, map_height));
}

/**
 * returns NULL if memory allocation fails.
 */
char	**copy_map_arr(t_map m)
{
	char	**map_copy;
	int		i;

	map_copy = (char **)ft_calloc((m.height + 1), sizeof(char *));
	if (map_copy == NULL)
		return (NULL);
	i = 0;
	while (i < m.height)
	{
		map_copy[i] = ft_strdup(m.map[i]);
		if (map_copy[i] == NULL)
			return (ft_free_arrstr(map_copy), NULL);
		i++;
	}
	return (map_copy);
}

t_errcode	check_map_closed(t_cub *cub)
{
	char	**map_copy;
	int		flood;

	map_copy = copy_map_arr(cub->smap);
	if (map_copy == NULL)
		return (destroy_cub(cub), ERR_MEM);
	map_copy[cub->smap.player_pos[0]][cub->smap.player_pos[1]] = '0';
	flood = apply_flood_fill(map_copy, cub->smap.player_pos[0],
			cub->smap.player_pos[1], cub->smap.height);
	//debug_int("flood", flood); //
	//ft_putarr_str(map_copy); //
	//debug_int("flood", flood); //
	ft_free_arrstr(map_copy);
	if (flood > 0)
		return (destroy_cub(cub), ERR_CUBNOTCLOSED);
	return (ERR_OK);
}
