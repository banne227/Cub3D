
#include "../../includes/cub3d.h"

int parse(int argc, char **argv, t_data *data)
{
    if (argc != 2 && argv[1] != NULL)
    {
        printf("Error\nInvalid number of arguments\n");
        return (1);
    }
    if (!extention_check(argv[1]) || !file_check(argv[1]))
        return (1);
    if (!get_data(argv[1], data))
        return (1); 
    return (0);
}