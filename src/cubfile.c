/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:18:11 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/03 16:48:38 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// t_errcode	check_mapline(char *line, int &max_width)
// {

// }

void	save_mapline(t_cub *cub, char *line)
{
	char	**map_tmp;
	int		i;

	if (!line)
		return ;
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

t_errcode	check_cub_map(t_cub *cub)
{

	//caracteres validos
		//que haya un solo caracter N,S,W,E
		//no espacios interm ni intros intermedios
	//que este rodeado de 1
	(void)cub;
	return ERR_OK;

}

static void	eat_newlines(int fd_in, char **line)
{
	debug("eating nl");
	while (*line && ft_strcmp(*line, "\n") != 0)
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
	check_cub_map(cub);
	return (e);
}
