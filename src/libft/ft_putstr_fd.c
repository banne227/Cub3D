/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:42:34 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/15 10:49:27 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int ret;

	i = 0;
	while (s[i])
	{
		ret = write(fd, &s[i], 1);
		if (ret == -1)
			return ;
		i++;
	}
}

// int main(void)
//{
//	ft_putstr_fd("abcde ds",1);
//	return (0);
//}