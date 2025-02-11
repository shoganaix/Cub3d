/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:18:11 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/11 14:50:50 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_errcode	check_mapline(char *line, int &max_width)
// {

// }

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
				*player_found = TRUE;
			else
				return (destroy_cub(cub), ERR_CUBINVALID);
		}
		if ((cub->smap.map[r][c] == ' ')
				&& !(!last || last == ' ' || last == '1'))
			return (destroy_cub(cub), ERR_CUBINVALIDSPC);
		last = cub->smap.map[r][c];
		c++;
	}
	return (ERR_OK);
}

	//caracteres validos : space, 1, 0, personaje
		//que haya un solo caracter N,S,W,E
		//no espacios interm ni intros intermedios
	//que este rodeado de 1
t_errcode	check_cub_map(t_cub *cub)
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
	e = check_cub_map(cub); //
	return (e);
}
