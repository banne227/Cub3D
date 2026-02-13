#include "../../includes/cub3d.h"

void *get_menu_image(t_game *game, char *filename)
{
    void	*menu_img;
    int	img_w = 0;
    int	img_h = 0;

    menu_img = mlx_xpm_file_to_image(game->mlx, filename, &img_w, &img_h);
    if (!menu_img)
    {        
        printf("Error\nFailed to load menu image: %s\n", filename);
        return (NULL);
    }
    return (menu_img);
}

void render_menu(t_game *game, t_data *data)
{  
    (void)data;
    void *menu_enter = get_menu_image(game, "./textures/menu/menu1.xpm");
    void *menu_quit = get_menu_image(game, "./textures/menu/menu2.xpm");
    void *menu = menu_enter;

    if (!menu_enter || !menu_quit)
        return;
    if (menu == menu_enter && (game->last_key == KEY_ENTER || game->last_key == KEY_SPACE))
    {
        mlx_clear_window(game->mlx, game->win);
        mlx_destroy_image(game->mlx, menu_enter);
        mlx_destroy_image(game->mlx, menu_quit);
        data->game.state = STATE_PLAY;
        data->game.menu_option = 0;
        // display_enter(data);
        return;
    }
    else if (menu == menu_quit && (game->last_key == KEY_ENTER || game->last_key == KEY_SPACE))
    {
        data->game.state = STATE_EXIT;
        game->menu_option = 1;
        mlx_clear_window(game->mlx, game->win);
        mlx_destroy_image(game->mlx, menu_enter);
        mlx_destroy_image(game->mlx, menu_quit);
        return;
    }
    if (menu == menu_enter && (game->last_key == KEY_DOWN || game->last_key == KEY_RIGHT))
        menu = menu_quit;
    else if (menu == menu_quit && (game->last_key == KEY_UP || game->last_key == KEY_LEFT))
        menu = menu_enter;
    mlx_clear_window(game->mlx, game->win);
    mlx_put_image_to_window(game->mlx, game->win, menu, 0, 0);
}