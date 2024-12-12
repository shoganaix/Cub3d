/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:33:50 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:52 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @return the index of the nl if contained, -1 otherwise
*/
static int	contains_nl(const char	*str)
{
	int	i;

	if (!str)
		return (-1);
	else
	{
		i = 0;
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			return (i);
		return (-1);
	}
}

/**
 * `*str` now starts from `pos`.
 * The new length of `*str` is `len(*str) - pos`.
 * 
 * Example: `*str = "aaaXyyy"` and `pos = 4` -> returns: `*str = "yyy"`
 * 
 * @param str a pointer to a string. The function changes it and also returns it.
 * @param pos the new starting position of the string
 * @return the same string but starting from `pos`. 
 * If `pos > len(*str)` it returns an empty string.
*/
static char	*reborn_from_pos(char **str, int pos)
{
	int	strlen;
	int	new_len;

	strlen = ft_strlen(*str);
	if (pos > strlen)
		new_len = 0;
	else
		new_len = strlen - pos + 1;
	*str = ft_str_realloc(*str, new_len, pos);
	if (!*str)
		return (NULL);
	return (*str);
}

static int	read_line(int fd, char **saved, int *nl_pos)
{
	char	*buf;
	int		ok;

	ok = 1;
	*nl_pos = contains_nl(*saved);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	while (*nl_pos < 0 && ok > 0)
	{
		ok = read(fd, buf, BUFFER_SIZE);
		if (ok <= 0)
			break ;
		buf[ok] = '\0';
		if (!ft_strjoin_realloc(saved, buf))
		{
			free(buf);
			return (-1);
		}
		*nl_pos = contains_nl(*saved);
	}
	free(buf);
	return (ok);
}

char	*get_next_line(int fd)
{
	static char	*saved[FOPEN_MAX];
	char		*line;
	int			nl_pos;
	int			ok;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	ok = read_line(fd, &saved[fd], &nl_pos);
	if (ok < 0 || (ok == 0 && (!saved[fd] || !saved[fd][0])))
	{
		if (saved[fd])
			saved[fd] = reborn_from_pos(&saved[fd], ft_strlen(saved[fd]) + 1);
		return (NULL);
	}
	if (ok == 0)
	{
		line = ft_strndup(saved[fd], -1);
		saved[fd] = reborn_from_pos(&saved[fd], ft_strlen(line) + 1);
	}
	else
	{
		line = ft_strndup(saved[fd], nl_pos + 1);
		saved[fd] = reborn_from_pos(&saved[fd], nl_pos + 1);
	}
	return (line);
}
