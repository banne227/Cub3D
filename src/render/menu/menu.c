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

void render_menu(t_game *game)
{   
    void *menu_img1 = get_menu_image(game, "./textures/menu/menu1.xpm");
    void *menu_img2 = get_menu_image(game, "./textures/menu/menu2.xpm");
    void *menu = menu_img1;

    if (!menu_img1 || !menu_img2)
        return;
    if (menu == menu_img1 && (game->last_key == KEY_ENTER || game->last_key == KEY_SPACE))
    {
        game->state = STATE_PLAY;
        mlx_clear_window(game->mlx, game->win);
        return;
    }
    else if (menu == menu_img2 && (game->last_key == KEY_ENTER || game->last_key == KEY_SPACE))
    {
        game->state = STATE_EXIT;
        mlx_clear_window(game->mlx, game->win);
        return;
    }
    if (menu == menu_img1 && (game->last_key == KEY_DOWN || game->last_key == KEY_RIGHT))
        menu = menu_img2;
    else if (menu == menu_img2 && (game->last_key == KEY_UP || game->last_key == KEY_LEFT   ))
        menu = menu_img1;
    mlx_put_image_to_window(game->mlx, game->win, menu, 0, 0);
}