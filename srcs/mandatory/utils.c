/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:33:16 by sehhong           #+#    #+#             */
/*   Updated: 2022/04/20 14:34:38 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ret;

	ret = malloc(size * count);
	if (!ret)
		return (0);
	memset(ret, 0, count * size);
	return (ret);
}
