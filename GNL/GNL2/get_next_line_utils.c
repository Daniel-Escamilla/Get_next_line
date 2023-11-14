/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:01:13 by descamil          #+#    #+#             */
/*   Updated: 2023/11/14 19:01:14 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int	ft_strlcpy(char *dest, const char *src, int len_dest)
{
	int	i;

	i = 0;
	if (len_dest <= ft_strlen(src))
	{
		if (len_dest == 0)
			return (ft_strlen(src));
		while (len_dest > 1)
		{	
			dest[i] = src[i];
			len_dest--;
			i++;
		}
		dest[i] = '\0';
		return (ft_strlen(src));
	}
	i = 0;
	while (i < len_dest - 1 && src[i] != '\0')
	{	
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		n;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	n = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = malloc(n + 1);
	if (ptr == NULL)
		return (NULL);
	while ((char)s1[i] != '\0')
	{	
		ptr[i] = (char)s1[i];
		i++;
	}
	while ((char)s2[j] != '\0')
	{
		ptr[i] = (char)s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}
