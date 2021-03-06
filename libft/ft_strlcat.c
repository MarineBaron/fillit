/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 12:05:53 by mbaron            #+#    #+#             */
/*   Updated: 2017/12/20 12:17:18 by mbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	slen;

	slen = 0;
	while (src[slen])
		slen++;
	i = 0;
	while (dst[i] && i < size)
		i++;
	j = 0;
	while (size && src[j] && i < size - 1)
		dst[i++] = src[j++];
	if (j)
	{
		dst[i] = '\0';
		return (slen + i - j);
	}
	return (slen + i);
}
