

#include "../../includes/cub3d.h"

char **realloc_map(char **map, int new_size)
{
	char **new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (new_size + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i + 1 < new_size )
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = NULL;
	new_map[i + 1] = NULL;
	free_tab(map);
	return (new_map);
}


char *trim_endf(char *line)
{
	int		len;
	char	*trimmed;

	len = 0;
	while (line[len] || line[len] != '\n')
		len++;
	if (len == 0)
		return (line);
	trimmed = malloc(sizeof(char) * (len + 1));
	if (!trimmed)
		return (NULL);
	trimmed = memcpy(trimmed, line, len);
	trimmed[len] = '\0';
	free(line);
	return (trimmed);
}

char **trim_file(char *file)
{
    int     size;
    char   **trimmed;
	char	*line;
	char	*tmp;
    
	size = 0;
	trimmed = NULL;
	line = get_next_line(file);
	while (line)
	{
		if (strcmp(line, "\n") != 0)
		{
			free(line);
			continue;
		} 
		trimmed = realloc_map(trimmed, size + 1);
		if (!trimmed)
			return (NULL);
		tmp = trim_endf(line);
		trimmed[size] = tmp;
		size++;
		free(tmp);
		line = get_next_line(file);
	}
	trimmed[size] = NULL;
	return (trimmed);
}

int get_data(char *filename, t_data *data)
{
	char **file;

	file = trim_file(filename);
	if (!file)
		return (0);
	if (!get_value(file, data))
		return (0);
	
    return (1);
}