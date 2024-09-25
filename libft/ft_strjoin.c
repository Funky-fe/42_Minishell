/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlima-fe <rlima-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 12:07:27 by rlima-fe          #+#    #+#             */
/*   Updated: 2023/04/22 12:07:48 by rlima-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*resultado;

	j = 0;
	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	resultado = malloc(sizeof(char) * len + 1);
	if (!resultado)
		return (NULL);
	i = 0;
	while (s1[i])
		resultado[j++] = s1[i++];
	i = 0;
	while (s2[i])
		resultado[j++] = s2[i++];
	resultado[j] = '\0' ;
	return (resultado);
}
