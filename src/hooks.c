/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:47:39 by llima-ce          #+#    #+#             */
/*   Updated: 2021/10/25 18:12:28 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		verify_move(t_module *module, char verify)
{
	if(verify == '0')
		return (0);
	if(verify == '1')
		return (1);
	if(verify == 'C')
	{
		module->coin->amount_taken = module->coin->amount_taken + 1;
		return(0);
	}
	if(verify == 'E')
	{
		if (module->coin->amount == 0)
			return(2);
		else
			return(1);
	}
	if(verify == 'J')
		return (3);
	else
		return (2);
}

void	move(t_module *module, int x, int y)
{
	int		res;

	res = verify_move(module, module->map->map[y][x]);
	if (res == 0)
	{
		module->player->player_step = module->player->player_step + 1;
		module->player->player_eye = 3;
		module->map->map[module->player->player_y]
			[module->player->player_x + 1] = 'P';
		module->map->map[module->player->player_y]
		[module->player->player_x] = '0';
		print_map(module);
	}
	else if (res == 1)
		module->player->player_eye = 3;
	else if (res == 2)
	{
		ft_printf("YOU WIN!\n");
		// destroy_all(module);
	}
	else if (res == 3)
	{
		ft_printf("GAME OVER!\n");
		// destroy_all(module);
	}
}

int key_hook(int keycode, t_module *module)
{
	printf("%d keycode\n", keycode);
	if(keycode == 113)
	{
		destroy_all(module);
		return (1);
	}
	if(keycode == KEY_D)
		move(module, module->player->player_x + 1, module->player->player_y);
	if(keycode == KEY_W)
		move(module, module->player->player_x - 1, module->player->player_y);
	if(keycode == KEY_A)
		move(module, module->player->player_x, module->player->player_y + 1);
	if(keycode == KEY_S)
		move(module, module->player->player_x, module->player->player_y - 1);
	return (0);
}

// void	close_window(t_module *module)
// {
	// mlx_hook(module->vars->win, 17, 1L<<17, destroy_all, module);
// }

int	hook(t_module *module)
{
	mlx_key_hook(module->vars->win, key_hook, module);
	mlx_loop(module->vars->mlx);
	return (0);
}
