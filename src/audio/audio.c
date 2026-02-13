/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by banne             #+#    #+#             */
/*   Updated: 2026/02/13 10:19:29 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void play_background_music(t_game *game)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        // Rediriger stdout et stderr pour éviter les messages
        freopen("/dev/null", "w", stdout);
        freopen("/dev/null", "w", stderr);
        
        // Lancer mpg123 en boucle infinie (-1) et silencieux (-q)
        execlp("mpg123", "mpg123", "-q", "--loop", "-1", 
               "./assets/music/Mortal_Kombat.mp3", NULL);
        
        // Si execlp échoue, on sort
        exit(1);
    }
    else if (pid > 0)
    {
        game->music_pid = pid;
        printf("🎵 Music started (PID: %d)\n", pid);
    }
    else
    {
        printf("Error: Failed to start music\n");
    }
}

void stop_background_music(t_game *game)
{
    if (game->music_pid > 0)
    {
        kill(game->music_pid, SIGTERM);
        game->music_pid = 0;
        printf("🔇 Music stopped\n");
    }
}