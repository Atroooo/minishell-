/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:28:26 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/08 14:46:53 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include <limits.h>

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

long long	ft_atoll(const char *str)
{
	int			sign;
	long long	nb;
	int			i;

	sign = 1;
	nb = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (((nb * 10) + str[i] - '0') / 10 != nb)
			return (-1);
		nb = (nb * 10) + str[i] - '0';
		if (!str[i + 1])
			return (nb * sign);
		i++;
	}
	return (0);
}
