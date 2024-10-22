/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittigl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:52:29 by lpittigl          #+#    #+#             */
/*   Updated: 2024/03/08 19:31:16 by lpittigl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	len(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s && s[len] && s[len] != -1)
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2, int i, int j)
{
	char	*final;

	if (!s2)
		return (NULL);
	final = (char *)malloc((len(s1) + BUFFER_SIZE + 1) * sizeof(char));
	if (!final)
		return (NULL);
	if (s1)
	{
		while (*(s1 + i))
		{
			final[i] = *(s1 + i);
			i++;
		}
	}
	while (*(s2 + j) != 0)
	{
		final[i + j] = *(s2 + j);
		j++;
	}
	final[i + j] = 0;
	if (s1)
		free(s1);
	return (final);
}

char	*ft_substr(char *s, size_t start, size_t len, int if_free)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (!s || len == 0 || s[i] == 0)
		return (NULL);
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = 0;
	if (if_free == 1)
		free(s);
	return (substr);
}
