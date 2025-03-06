/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:46:09 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/06 16:40:01 by msoriano         ###   ########.fr       */
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
