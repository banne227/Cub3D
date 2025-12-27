
#include "../../includes/cub3d.h"

bool have_digit(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] >= '0' && line[i] <= '9')
            return (true);
        i++;
    }
    return (false);
}

int get_first_map_index(char **file)
{
    int i;

    i = 0;
    while (file[i])
    {
        if (have_digit(file[i]))
            return (i);
        i++;
    }
    return (-1);
}

char *trim_spaces(char *line, int size)
{
    char	*trimmed;
    int     i;

    trimmed = malloc(sizeof(char) * (size + 1));
    i = 0;
    while (line[i] == ' ')
    {
        trimmed[i] = '0';
        i++;
    }
    while (line[i])
    {
        trimmed[i] = line[i];
        i++;
    }
    while (i <= size)
    {
        trimmed[i] = '0';
        i++;
    }
    i = ft_strlen(line) - 1;
    while (line[i] == ' ')
    {
        trimmed[i] = '0';
        i--;
    }
    trimmed[size + 1] = '\0';
    free(line);
    return (trimmed);
}

int max_len(char **file, int start_index, int map_size)
{
    int max;
    int len;
    int i;

    max = 0;
    i = 0;
    while (i < map_size)
    {
        len = ft_strlen(file[start_index + i]);
        if (len > max)
            max = len;
        i++;
    }
    return (max - 1);
} 

char **get_map(char **file, t_data *data)
{
    int     map_size;
    char  **map;
    int     start_index;
    int    i;
    char   *trimmed_line;

    start_index = get_first_map_index(file);
    map_size = 0;
    while (file[start_index + map_size])
        map_size++;
    map = malloc(sizeof(char *) * (map_size + 1));
    if (!map)
        return (NULL);
    i = 0;
    while (i < map_size)
    {
        trimmed_line = trim_endf(ft_strdup(file[start_index + i]));
        if (!trimmed_line)
            return (NULL);
        trimmed_line = trim_spaces(trimmed_line, max_len(file, start_index, map_size));
        if (!trimmed_line)
            return (NULL);
        map[i] = trimmed_line;
        i++;
    }
    data->map.map = map;
    data->map.width = max_len(file, start_index, map_size) + 1;
    data->map.height = map_size;
    map[i] = NULL;
    return (map);
}