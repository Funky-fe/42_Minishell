/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubenfernandes <rubenfernandes@student.42. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:01:38 by rlima-fe          #+#    #+#             */
/*   Updated: 2023/04/22 21:00:38 by rubenfernandes   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	x;

	i = 0;
	n = 1;
	x = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+' )
	{
		if (str[i] == '-' )
			n = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' )
	{
		x = (x * 10) + (str[i] - 48);
		i++;
	}
	return (x * n);
}
