/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:49:57 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 17:49:58 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	*get_menu_image(t_game *game, char *filename)
{
	void	*menu_img;
	int		img_w;
	int		img_h;

	img_w = 0;
	img_h = 0;
	menu_img = mlx_xpm_file_to_image(game->mlx, filename, &img_w, &img_h);
	if (!menu_img)
	{
		printf("Error\nFailed to load menu image: %s\n", filename);
		return (NULL);
	}
	return (menu_img);
}

static void	help_render_menu(t_data *data, void *menu_enter, void *menu_quit)
{
	t_game *game;

	game = &data->game;
	if (game->last_key == KEY_ENTER || game->last_key == KEY_SPACE)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_image(game->mlx, menu_enter);
		mlx_destroy_image(game->mlx, menu_quit);
		if (game->menu_option == 0)
		{
			init_anim(data);
			data->game.state = STATE_ANIMATION;
			return ;
		}
		data->game.state = STATE_EXIT;
		close_game(data);
		return ;
	}
}

void	render_menu(t_game *game, t_data *data)
{
	void	*menu_enter;
	void	*menu_quit;
	void	*menu;

	menu_enter = get_menu_image(game, "./textures/menu/menu1.xpm");
	menu_quit = get_menu_image(game, "./textures/menu/menu2.xpm");
	if (!menu_enter || !menu_quit)
		return ;
	if (game->last_key == KEY_DOWN || game->last_key == KEY_RIGHT)
		game->menu_option = 1;
	else if (game->last_key == KEY_UP || game->last_key == KEY_LEFT)
		game->menu_option = 0;
	if (game->menu_option == 0)
		menu = menu_enter;
	else
		menu = menu_quit;
	help_render_menu(data, menu_enter, menu_quit);
	mlx_clear_window(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, menu, 0, 0);
	mlx_destroy_image(game->mlx, menu_enter);
	mlx_destroy_image(game->mlx, menu_quit);
}
