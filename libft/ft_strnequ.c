/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 08:31:22 by mbaron            #+#    #+#             */
/*   Updated: 2017/12/21 14:35:47 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	if ((!s1 && !s2) || !n)
		return (1);
	if (!s1 || !s2)
		return (0);
	i = 0;
	while (i < n - 1 && s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] == s2[i]);
}
