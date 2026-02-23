/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by banne             #+#    #+#             */
/*   Updated: 2026/02/23 10:38:43 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

pid_t	play_sounds(char *path)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execlp("paplay", "paplay", path, NULL);
		exit(1);
	}
	else if (pid < 0)
	{
		printf("Error: Failed to fork for sound %s\n", path);
		return (0);
	}
	return (pid);
}

void	stop_sounds(pid_t pid)
{
	if (pid > 0)
	{
		kill(pid, SIGTERM);
		waitpid(pid, NULL, 0);
	}
}
