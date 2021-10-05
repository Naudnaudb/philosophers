/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abordack <abordack@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:09:10 by abordack          #+#    #+#             */
/*   Updated: 2021/09/28 18:09:17 by abordack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	error(char *str)
{
	printf("ERROR:\n%s\n", str);
	exit(1);
}

int	ft_malloc(void *dst, size_t size)
{
	*(void **)dst = malloc(size);
	if (*(void **)dst == NULL)
		return (1);
	memset(*(void **)dst, 0, size);
	return (0);
}
