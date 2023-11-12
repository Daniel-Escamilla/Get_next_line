/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:24:27 by marvin            #+#    #+#             */
/*   Updated: 2023/11/10 20:24:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

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

char	*ft_get_next_line(int fd)
{
	static char	*buffer;
	char		*str;
	char		*str_old;
	char		*tmp;
	int			bytesRead;
	int			i;
	int			j;

	i = 0;
	j = 0;
	str = NULL;
	str_old = NULL;
	while (j != -1)
	{
		if (buffer == 0)
		{
			buffer = malloc(BUFFER_SIZE);
			if (buffer == NULL)
				return(NULL);
			bytesRead = read(fd, buffer, BUFFER_SIZE);
			if (bytesRead <= 0)
				return(NULL);
		}
		printf("BUFF = %s\n", buffer);
		tmp = malloc(bytesRead + 1);

		if (tmp == NULL)
			return (NULL);

		while (i < bytesRead)
		{
			if (buffer[i] == '\\' && buffer[i + 1] == 'n')
				break;
			tmp[i] = buffer[i];
			i++;
		}
		// printf("I = %d\n", i);
		
		
		
		if (str == NULL && i == bytesRead)
		{
			tmp[i] = '\0';
			str_old = 0;
			str = ft_strjoin(str_old, tmp);

			if (str == NULL);
				return(NULL);
			// printf("%s\n", str);
			i = 0;
			free(str_old);
			while (i < bytesRead)
			{
				tmp[i] = 0;
				i++;
			}
			buffer = 0;
			// printf("BUFFER = %s\n", buffer);
		}
		if (str != NULL && i == bytesRead)
		{	
			str = tmp;
			buffer = 0;
			printf("STR = %s\n", str);
		}
		else if (i < bytesRead)
		{
			j = 0;
			i += 2;
			// printf("A = %s\n", buffer);
			while (i < bytesRead)
			{
				buffer[j] = buffer[i];
				i++;
				j++;
			}
			// printf("J = %d\n", j);
			// printf("C = %s\n", buffer);
			// printf("%d\n", i);
			// printf("%d\n", j);
			while (j < bytesRead)
			{
				buffer[j] = 0;
				j++;
			}
			
			j = -1;
		}
		return (str);
	}
	return (str);
}

int main()
{
	int		fd;
	char	*line;
	int		i;

	i = 4;
	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while (i > 0)
	{
		line = ft_get_next_line(fd);
		if (line != NULL);
			printf("FINAL: %s\n", line);
		free(line);
		i--;
	}
	close(fd);
	return(0);
}