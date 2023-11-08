/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:00:27 by descamil          #+#    #+#             */
/*   Updated: 2023/11/08 17:40:58 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void    ft_putchar(char c)
{
    write(1, &c, 1);
}
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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
    static int  index;
    char        *str;
    char        *old_str;
    char        *tmp;
    int         bytesRead;
    int         num_to_cpy;
    int         i;

    index = 0;
    str = NULL;
    while (1)
    {
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
        while (i < BUFFER_SIZE && buffer[i] != '\n')
            i++;
        num_to_cpy = i - index;
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
            free (old_str);
            free (tmp);
        }
        else
            str = tmp;
        index = i;
        if (i < BUFFER_SIZE && buffer[i] == '\n')
        {
            index++;
            return (str);
        }
        if (i == BUFFER_SIZE)
            index = 0;
    }
}

int main()
{
    int     fd = open("text.txt", O_RDONLY);
    char    *line;
    int     i;

    if (fd == -1)
        return (1);
    i = 1;
    while (i > 0)
    {
        line = get_next_line(fd);
        if (line == NULL)
        {
            close (fd);
            return (1);
        }
        printf("%s\n", line);
        free(line);
        i--;
    }
    close(fd);
    return (0);
}
/* 
    static char buffer[BUFFER_SIZE];
    static  int index;
    char        *str;
    int         i;
    int         bytesRead;
    int         j;
    int         k;

    index = 0;
    str = NULL;
    
    if (index == 0)
        bytesRead = ft_read_buffer(fd, buffer, BUFFER_SIZE);
    i = index;
    while (i < bytesRead)
    {
        if (buffer[i] == '\\' && buffer[i + 1] == 'n')
        {
            str = (char *)malloc(i - index + 2);
            if (str == NULL)
                exit(1);
            j = 0;
            k = 0;
            while (k <= i)
            {
                str[j] = buffer[k];
                k++;
                j++;
                //printf("%s\n", str);
            }
            str[j] = '\n';
            str[j + 1] = '\0';
            return (str);
        }
        i++;
        index += 1;
        printf("%d\n", index);
    }
    if (i == bytesRead)
    {
        index = 0;
        return (get_next_line(fd));
    }
    return (NULL);
*/