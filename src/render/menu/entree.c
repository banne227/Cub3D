#include "../../includes/cub3d.h"

void display_img(t_data *data, void *img)
{
    int h;
    int w;

    h = 0;
    w = 0;
    mlx_put_image_to_window(data->game.mlx, data->game.win, img, w, h);
    usleep(200000);
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
    mlx_destroy_image(data->game.mlx, data->enter.ent1);
    mlx_destroy_image(data->game.mlx, data->enter.ent2);
    mlx_destroy_image(data->game.mlx, data->enter.ent3);
    mlx_destroy_image(data->game.mlx, data->enter.ent4);
    mlx_destroy_image(data->game.mlx, data->enter.ent5);
    mlx_destroy_image(data->game.mlx, data->enter.ent6);
    mlx_destroy_image(data->game.mlx, data->enter.ent7);
    mlx_destroy_image(data->game.mlx, data->enter.ent8);
    mlx_destroy_image(data->game.mlx, data->enter.ent9);
}

void display_enter(t_data *data)
{
    t_enter *enter = &data->enter;
    void *img;

    display_img(data, enter->ent1);
    display_img(data, enter->ent2);
    display_img(data, enter->ent3);
    display_img(data, enter->ent4);
    display_img(data, enter->ent5);
    display_img(data, enter->ent6);
    display_img(data, enter->ent7);
    display_img(data, enter->ent8);
    display_img(data, enter->ent9);
    destroy_enter(data);
    data->game.state = STATE_PLAY;
    data->game.menu_option = 0;
}