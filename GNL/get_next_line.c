/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:00:27 by descamil          #+#    #+#             */
/*   Updated: 2023/11/09 13:17:05 by descamil         ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int	    n;
	char	*ptr;
	int	    i;
	int	    j;

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

int ft_read_buffer(int fd, char *buffer, int size)
{
    int     bytesRead;
    
    bytesRead = read(fd, buffer, size);
    return (bytesRead); 
}

char    *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static char *tmp;
    static int  index;
    static int  x;
    char        *str;
    char        *old_str;
    int         bytesRead;
    int         num_to_cpy;
    int         i;
    int         j;

    index = 0;
    x = 0;
    str = NULL;
    while (1)
    {
//        printf("Tmp = %s\n\n", tmp);
        if (index == 0)
        {
            bytesRead = ft_read_buffer(fd, buffer, BUFFER_SIZE);
            if (bytesRead <= 0)
            {
                if (str != NULL)
                    free(str);
                return (NULL); 
            }
        }
        i = index;
        while (i < BUFFER_SIZE)
        {
            if (buffer[i] == '\\' && buffer[i + 1] == 'n')
                break;
            i++;
        }
        num_to_cpy = i - index;
        // printf("Buffer: %s\n", buffer);
        tmp = malloc(num_to_cpy + 1);
        if (tmp == NULL)
        {
            if (str != NULL)
                free(str);
            return (NULL);
        }
        ft_strlcpy(tmp, &buffer[index], num_to_cpy + 1);
        if (str != NULL)
        {
            old_str = str;
            str = ft_strjoin(old_str, tmp);
            // printf("tmp: %s\n", str);
            // printf("old: %s\n", str);
            free (old_str);
            free (tmp);
        }
        else
            str = tmp;
        index = i;
        // printf("I = %d\n", i);
        if (i < BUFFER_SIZE && ft_strchr(buffer, '\n') == NULL)
        {
            index = 0;
            str[x * 10 + i] = '\n';
            j = 0;
            i += 2;
            while (i < BUFFER_SIZE)
            {
                tmp[j] = buffer[i];
                i++;
                j++;
            }
            tmp[j] = '\0';
            break;
        }
        if (i == BUFFER_SIZE)
            index = 0;
        x++;
    }
//    printf("TMP = %s\n", tmp);
    return (str);
}

int main()
{
    int     fd = open("text.txt", O_RDONLY);
    char    *line;
    int     i;

    if (fd == -1)
        return (1);
    i = 2;
    while (i > 0)
    {
        line = get_next_line(fd);
        printf("%s", line);
        free(line);
        i--;
    }
    close(fd);
    return (0);
}