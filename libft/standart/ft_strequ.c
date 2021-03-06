/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:17:37 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:17:37 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int	res;

	if (!s1 || !s2)
		return (0);
	res = (ft_strcmp(s1, s2) == 0) ? 1 : 0;
	return (res);
}
