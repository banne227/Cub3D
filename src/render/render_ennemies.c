#include "../../includes/cub3d.h"

typedef struct s_sprite_utils
{
    double transform_x;
    double transform_y;
    int sprite_screen_x;
    int line_height;
    int draw_start_x;    
    int draw_end_x;      
    int draw_start;
    int draw_end;
    t_img *img;
} t_sprite_utils;

// Calcule la transformation sprite de l'espace monde vers l'espace caméra
// Équivalent de calculate_ray_dir() mais pour un sprite à une position donnée
static void calculate_transform(t_game *game, t_ennemy *e,
                                       t_sprite_utils *utils)
{
    double rel_x;
    double rel_y;
    double inv_det;

    // Position relative du sprite par rapport au joueur
    rel_x = e->pos.x + 0.5 - game->player.pos_x;
    rel_y = e->pos.y + 0.5 - game->player.pos_y;

    // Inverse du déterminant de la matrice caméra (même calcul que raycasting)
    inv_det = 1.0 / (game->player.plane_x * game->player.dir_y - game->player.dir_x * game->player.plane_y);

    // Transformation dans l'espace caméra (formules standard sprite raycasting)
    // transform_x = composante horizontale, transform_y = profondeur
    utils->transform_x = inv_det * (game->player.dir_y * rel_x - game->player.dir_x * rel_y);
    utils->transform_y = inv_det * (-game->player.plane_y * rel_x + game->player.plane_x * rel_y);
}

// Crée une t_img wrapper pour un sprite ennemi (carré 64x64)
// Permet de réutiliser get_texture_color() du raycasting (raycasting.c)
static t_img create_sprite_img(void *mlx_img)
{
    t_img img;

    img.img = mlx_img;
    // Récupère addr avec mlx_get_data_addr comme pour les textures murs
    img.addr = mlx_get_data_addr(mlx_img, &img.bits_per_pixel,
                                 &img.line_length, &img.endian);
    // Dimensions fixes des sprites ennemis (carrés 64x64)
    img.width = 64;
    img.height = 64;
    return (img);
}

// Calcule les dimensions du sprite à l'écran
// RÉUTILISE pixel_to_fill() de raycasting_utils.c pour calculer line_height
static int calculate_dimensions(t_sprite_utils *sprite,
                                       t_game *game)
{
    t_raycasting_utils utils;

    // transform_y = distance perpendiculaire, comme perp_wall_dist du raycasting
    utils.perp_wall_dist = sprite->transform_y;

    // APPEL DIRECT À pixel_to_fill() (raycasting_utils.c)
    // Calcule line_height, draw_start, draw_end exactement comme pour les murs
    sprite->line_height = pixel_to_fill(&utils, game);
    sprite->draw_start = utils.draw_start; // Récupéré de pixel_to_fill()
    sprite->draw_end = utils.draw_end;     // Récupéré de pixel_to_fill()

    // Position X du sprite à l'écran (formule standard projection sprite)
    sprite->sprite_screen_x = (int)((game->win_w / 2.0) * (1 + sprite->transform_x / sprite->transform_y));

    // Bornes X du sprite (carré donc largeur = hauteur)
    sprite->draw_start_x = -sprite->line_height / 2 + sprite->sprite_screen_x;
    sprite->draw_end_x = sprite->line_height / 2 + sprite->sprite_screen_x;

    // Clipping X (ne pas dépasser l'écran)
    if (sprite->draw_start_x < 0)
        sprite->draw_start_x = 0;
    if (sprite->draw_end_x >= game->win_w)
        sprite->draw_end_x = game->win_w - 1;
    return (sprite->line_height);
}

// Calcule img_x pour le sprite
// Version simplifiée de convert_coords_textures() (raycasting_utils.c)
// Pour un sprite : interpolation linéaire simple entre draw_start_x et draw_end_x
static int get_sprite_tex_x(t_sprite_utils *sprite, int x)
{
    int img_x;

    // Interpolation linéaire : position dans le sprite proportionnelle à x
    // Similaire au calcul de wall_x dans convert_coords_textures()
    img_x = (int)((x - sprite->draw_start_x) * sprite->img->width / (double)sprite->line_height);

    // Clipping pour rester dans la texture (même logique que convert_coords_textures)
    if (img_x < 0)
        img_x = 0;
    if (img_x >= sprite->img->width)
        img_x = sprite->img->width - 1;
    return (img_x);
}

// Dessine une colonne verticale du sprite
// RÉUTILISE LA MÊME LOGIQUE que draw_textured_line() (raycasting.c)
// Utilise step, tex_pos, img_y avec les mêmes calculs exactement
static void draw_sprite_stripe(t_game *game, t_sprite_utils *utils, int x)
{
    int y;
    double step;    // Pas d'interpolation (même variable que draw_textured_line)
    double tex_pos; // Position dans la texture (même variable que draw_textured_line)
    int img_y;      // Coordonnée Y texture (même variable que draw_textured_line)
    int color;
    int img_x;

    // Clipping X
    if (x < 0 || x >= game->win_w)
        return;
    // Z-buffer check : ne dessine que si sprite plus proche que le mur
    // (game->z_buffer rempli par raycasting.c ligne 107)
    if (utils->transform_y <= 0 || utils->transform_y >= game->z_buffer[x])
        return;

    // Calcule coordonnée X de la texture
    img_x = get_sprite_tex_x(utils, x);

    // MÊME CALCUL que draw_textured_line() (raycasting.c ligne 43-44)
    step = (double)utils->img->height / utils->line_height;
    tex_pos = (utils->draw_start - game->win_h / 2 + utils->line_height / 2) * step;

    // Boucle sur Y : MÊME LOGIQUE que draw_textured_line() (raycasting.c ligne 45-56)
    y = utils->draw_start;
    while (y < utils->draw_end)
    {
        img_y = (int)tex_pos;
        if (img_y < 0)
            img_y = 0;
        if (img_y >= utils->img->height)
            img_y = utils->img->height - 1;
        tex_pos += step;

        // APPEL DIRECT À get_texture_color() (raycasting.c ligne 17)
        color = get_texture_color(utils->img, img_x, img_y);

        // Transparence : ne dessine pas le noir (0x000000)
        if (color != 0x000000)
            my_mlx_pixel_put(game, x, y, color); // APPEL DIRECT (raycasting.c ligne 26)
        y++;
    }
}

// Effectue le "raycasting" d'un seul sprite ennemi
// Structure similaire à raycasting() (raycasting.c ligne 86-111)
// Boucle while sur x comme raycasting.c ligne 91
static void spritecast_one(t_game *game, t_ennemy *e)
{
    t_sprite_utils utils;
    t_img sprite_img;
    int x;

    if (!e || !e->display || !game->z_buffer)
        return;

    // 1. Transformation (équivalent de calculate_ray_dir, raycasting.c ligne 93)
    calculate_transform(game, e, &utils);

    // Culling : sprite derrière la caméra
    if (utils.transform_y <= 0.01)
        return;

    // 2. Crée t_img wrapper pour réutiliser get_texture_color()
    sprite_img = create_sprite_img(e->display);
    utils.img = &sprite_img;

    // 3. Calcule dimensions (utilise pixel_to_fill, raycasting.c ligne 104)
    calculate_dimensions(&utils, game);

    // 4. Boucle sur X : dessine chaque colonne du sprite
    // MÊME STRUCTURE que raycasting.c ligne 91 : while (x < game->win_w)
    x = utils.draw_start_x;
    while (x < utils.draw_end_x)
    {
        draw_sprite_stripe(game, &utils, x); // Équivalent de draw_textured_line()
        x++;
    }
}


void render_ennemies(t_game *game)
{
    t_ennemy *e;

    e = game->ennemys;
    while (e)
    {
        if (e->alive)
        {
            if (e->hit_frame > 0)
            {
                e->display = e->img[2];
                e->hit_frame--;
            }
            else
            {
                e->display = e->img[0];
            }
        }
        else
        {
            e->display = e->img[3];
        }
        spritecast_one(game, e);
        e = e->next;
    }
}
