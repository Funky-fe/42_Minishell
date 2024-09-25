/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlima-fe <rlima-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:02:34 by rlima-fe          #+#    #+#             */
/*   Updated: 2023/04/13 10:40:22 by rlima-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	check;
	char	*sub;

	i = 0;
	if (start >= ft_strlen(s))
	{
		sub = malloc(sizeof(char));
		*sub = '\0' ;
		return (sub);
	}
	check = ft_strlen(s) + start;
	if (len > check)
		len = check;
	sub = malloc((sizeof(char)) * (len + 1));
	if (!sub)
		return (NULL);
	while (start < ft_strlen(s) && i < len)
		sub[i++] = s[start++];
	sub[i] = '\0' ;
	return (sub);
}
