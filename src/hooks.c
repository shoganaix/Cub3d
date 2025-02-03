/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:02:57 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/03 13:45:58 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_hndlr(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	debug_int("key pressed", keycode);
	if (keycode == KEY_ESC)
		close_window(game);
	if (keycode == KEY_A)
		debug("pressed A");
	if (keycode == KEY_S)
		debug("pressed S");
	if (keycode == KEY_W)
		debug("pressed W");
	if (keycode == KEY_D)
		debug("pressed D");
	if (keycode == KEY_LEFT)
		debug("pressed <-");
	if (keycode == KEY_RIGHT)
		debug("pressed ->");
	return (0);
}
