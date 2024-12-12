/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:51:54 by macastro          #+#    #+#             */
/*   Updated: 2024/10/16 18:41:22 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * It sends the char 'c' to the file descriptor specified
 * 
 * @param c the character to write
 * @param fd the file descriptor where to wirte
 * @return void
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
