/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:39:44 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/23 08:42:14 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	int	ret;

	ret = (int)write(fd, &c, 1);
	(void)ret;
}

// int main(void)
//{
//	ft_putchar_fd('e',1);
//	return (0);
//}