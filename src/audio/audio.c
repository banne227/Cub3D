/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by banne             #+#    #+#             */
/*   Updated: 2026/02/16 14:19:44 by banne            ###   ########.fr       */
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

void	play_background_music(t_game *game)
{
	pid_t	pid;

	if (!game->background_music)
		return ;
	pid = fork();
	if (pid == 0)
	{
		execlp("paplay", "paplay", BACKGROUND_SOUND, NULL);
		exit(1);
	}
	else if (pid > 0)
	{
		game->music_pid = pid;
		printf("Music started \n");
	}
	else
	{
		printf("Error: Failed to start music\n");
	}
}

void	stop_background_music(t_game *game)
{
	if (!game->background_music)
		return ;
	if (game->music_pid > 0)
	{
		kill(game->music_pid, SIGTERM);
		waitpid(game->music_pid, NULL, 0);
		game->music_pid = 0;
		printf("Music stopped\n");
	}
}
