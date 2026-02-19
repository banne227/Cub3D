/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:46:13 by jhauvill          #+#    #+#             */
/*   Updated: 2025/10/15 10:49:10 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
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
	ret = write(fd, "\n", 1);
	if (ret == -1)
		return ;
}

// int main(void)
//{
//	ft_putendl_fd("abcd",1);
//	return (0);
//}