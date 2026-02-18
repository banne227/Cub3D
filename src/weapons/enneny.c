

#include "../../includes/cub3d.h"

take_damage(int damage, int pos_x, int pos_y)
{
    t_ennemy ennemy;

    ennemy = get_ennemy_at(pos_x, pos_y);
    ennemy.display = ennemy.img[2];
    if (ennemy.alive)
    {
        ennemy.health -= damage;
        if (ennemy.health <= 0)
        {
            ennemy.alive = false;
            ennemy.display = ennemy.img[3];
            // play death sound
        }
    }
}