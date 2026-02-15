
#include "../../includes/cub3d.h"

void make_action(t_data *data, int keycode)
{
    if (keycode == MOUSE_LEFT)
    {
        if (data->game.weapon.type == 0)
            cut(&data->game.weapon, &data->game);
        else if (data->game.weapon.type == 1)
            shoot(&data->game.weapon, &data->game);
    }
    else if (keycode == MOUSE_RIGHT || keycode == KEY_R)
        reload(&data->game.weapon);
    else if (keycode == KEY_M)
    {
        data->game.state = STATE_MENU;
        stop_background_music(&data->game);
    }
    else if (keycode == KEY_SPACE)
        swap_weapon(&data->game);
}