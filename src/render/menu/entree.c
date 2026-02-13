#include "../../includes/cub3d.h"

void display_img(t_data *data, void *img)
{
    int h;
    int w;

    if (!img || !data->game.mlx || !data->game.win)
        return;
    h = 0;
    w = 0;
    mlx_clear_window(data->game.mlx, data->game.win);
    mlx_put_image_to_window(data->game.mlx, data->game.win, img, w, h);
}

t_enter load_enter(void *mlx)
{
    t_enter enter;
    int w, h;

    w = 0;
    h = 0;

    enter.ent1 = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter1.xpm", &w, &h);
    enter.ent2 = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter2.xpm", &w, &h);
    enter.ent3 = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter3.xpm", &w, &h);
    enter.ent4 = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter4.xpm", &w, &h);
    enter.ent5 = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter5.xpm", &w, &h);
    enter.ent6 = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter6.xpm", &w, &h);
    enter.ent7 = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter7.xpm", &w, &h);
    enter.ent8 = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter8.xpm", &w, &h);
    enter.ent9 = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter9.xpm", &w, &h);
    return enter;
}

void destroy_enter(t_data *data)
{
    destroy_img(data->game.mlx, data->enter.ent1);
    destroy_img(data->game.mlx, data->enter.ent2);
    destroy_img(data->game.mlx, data->enter.ent3);
    destroy_img(data->game.mlx, data->enter.ent4);
    destroy_img(data->game.mlx, data->enter.ent5);
    destroy_img(data->game.mlx, data->enter.ent6);
    destroy_img(data->game.mlx, data->enter.ent7);
    destroy_img(data->game.mlx, data->enter.ent8);
    destroy_img(data->game.mlx, data->enter.ent9);
}

void init_anim(t_data *data)
{
    data->enter = load_enter(data->game.mlx);
    data->enter_frame = 0;
    data->last_frame_time = timestamp();
}


void display_enter(t_data *data)
{
    data->enter = load_enter(data->game.mlx);
    if (data->enter_frame == 0)
        display_img(data, data->enter.ent1);
    else if (data->enter_frame == 1)
        display_img(data, data->enter.ent2);
    else if (data->enter_frame == 2)
        display_img(data, data->enter.ent3);
    else if (data->enter_frame == 3)
        display_img(data, data->enter.ent4);
    else if (data->enter_frame == 4)
        display_img(data, data->enter.ent5);
    else if (data->enter_frame == 5)
        display_img(data, data->enter.ent6);
    else if (data->enter_frame == 6)
        display_img(data, data->enter.ent7);
    else if (data->enter_frame == 7)
        display_img(data, data->enter.ent8);
    else if (data->enter_frame == 8)
        display_img(data, data->enter.ent9);
    if (data->enter_frame > 8)
    {
        data->enter_frame = 0;
        destroy_enter(data);
        data->game.state = STATE_PLAY;
        data->game.menu_option = 0;
    }
    if (timestamp() - data->last_frame_time > 100)
    {
        data->enter_frame++;
        data->last_frame_time = timestamp();
    }
}
