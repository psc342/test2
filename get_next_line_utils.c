/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangchpa <sangchpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:49:10 by sangchpa          #+#    #+#             */
/*   Updated: 2021/02/05 16:23:57 by sangchpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char		*ft_strdup(const char *s1)
{
	int		i;
	int		s1_len;
	char	*p;

	i = 0;
	s1_len = ft_strlen(s1);
	p = (char*)malloc((s1_len + 1) * sizeof(char));
	if (p == 0)
		return (0);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	if (dst == 0 && src == 0)
		return (0);
	i = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (i < len && (i + 1) < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (len);
}


size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = dst_len;
	j = 0;
	if (dst_len > dstsize)
		return (src_len + dstsize);
	while (((dst_len + j + 1) < dstsize) && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (src_len + dst_len);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		s1_len;
	int		s2_len;

	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (p == 0)
		return (0);
	ft_strlcpy(p, s1, s1_len + 1);
	ft_strlcat((p + s1_len), s2, s2_len + 1);
	return (p);
}
