#include "../../includes/cub3d.h"

void display_img(t_data *data, void *img)
{
    int h;
    int w;

    if (!img || !data->game.mlx || !data->game.win)
        return;
    h = 0;
    w = 0;
    if (data->anim.last_img != img)
    {
        mlx_clear_window(data->game.mlx, data->game.win);
        printf("Displaying image %p\n", img);
    }
    mlx_put_image_to_window(data->game.mlx, data->game.win, img, w, h);
    data->anim.last_img = img;
}

void load_enter(void *mlx, t_anim *enter)
{
    int w, h;

    w = 0;
    h = 0;

    enter->ent[0] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter0.xpm", &w, &h);
    enter->ent[1] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter1.xpm", &w, &h);
    enter->ent[2] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter2.xpm", &w, &h);
    enter->ent[3] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter3.xpm", &w, &h);
    enter->ent[4] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter4.xpm", &w, &h);
    enter->ent[5] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter5.xpm", &w, &h);
    enter->ent[6] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter6.xpm", &w, &h);
    enter->ent[7] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter7.xpm", &w, &h);
    enter->ent[8] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter8.xpm", &w, &h);
    enter->ent[9] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter9.xpm", &w, &h);
}

void destroy_enter(t_data *data)
{
    int i;

    i = 0;
    while (i < 10)
    {
        if (data->anim.ent[i])
            destroy_img(data->game.mlx, data->anim.ent[i]);
        i++;
    }
}

void init_anim(t_data *data)
{
    load_enter(data->game.mlx, &data->anim);
    data->anim.last_frame_time = timestamp();
}


void display_enter(t_data *data)
{
    if (data->anim.enter_frame == 0)
        display_img(data, data->anim.ent[0]);
    else if (data->anim.enter_frame == 1)
        display_img(data, data->anim.ent[1]);
    else if (data->anim.enter_frame == 2)
        display_img(data, data->anim.ent[2]);
    else if (data->anim.enter_frame == 3)
        display_img(data, data->anim.ent[3]);
    else if (data->anim.enter_frame == 4)
        display_img(data, data->anim.ent[4]);
    else if (data->anim.enter_frame == 5)
        display_img(data, data->anim.ent[5]);
    else if (data->anim.enter_frame == 6)
        display_img(data, data->anim.ent[6]);
    else if (data->anim.enter_frame == 7)
        display_img(data, data->anim.ent[7]);
    else if (data->anim.enter_frame == 8)
        display_img(data, data->anim.ent[8]);
    else if (data->anim.enter_frame == 9)
        display_img(data, data->anim.ent[9]);
    else
    {
        destroy_enter(data);
        data->game.state = STATE_PLAY;
        data->game.menu_option = 0;
        return;
    }
    
    if (timestamp() - data->anim.last_frame_time > 175)
    {
        data->anim.enter_frame++;
        data->anim.last_frame_time = timestamp();
    }
}
