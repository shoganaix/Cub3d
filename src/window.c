/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:46:09 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/19 16:32:43 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// frees, destroys ??
int	close_window(t_game *game)
{
	destroy_game(game);
	ft_printf("Bye bye\n");
	exit(0);
}
