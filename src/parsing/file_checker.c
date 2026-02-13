/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 09:15:32 by banne             #+#    #+#             */
/*   Updated: 2026/02/13 16:50:03 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	extension_check(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 4)
	{
		printf("Error\nFilename too short to have a valid extension\n");
		return (false);
	}
	if (filename[len - 4] != '.' || filename[len - 3] != 'c' || filename[len
		- 2] != 'u' || filename[len - 1] != 'b')
	{
		printf("Error\nInvalid file extension. Expected .cub\n");
		return (false);
	}
	return (true);
}

bool	file_check(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCould not open file: %s\n", filename);
		return (false);
	}
	close(fd);
	return (true);
}