/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlima-fe <rlima-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:36:24 by rlima-fe          #+#    #+#             */
/*   Updated: 2023/04/13 10:48:30 by rlima-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*st1;
	char	*st2;
	size_t	i;

	i = 0;
	st1 = (char *)s1;
	st2 = (char *)s2;
	while (i < n)
	{
		if (st1[i] != st2[i])
			return ((unsigned char)st1[i] - ((unsigned char)st2[i]));
		i++;
	}
	return (0);
}
