/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:00:27 by descamil          #+#    #+#             */
/*   Updated: 2023/11/14 19:03:43 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*str;
	char		*str_old;
	char		*tmp;
	int			bytesread;
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	str_old = NULL;
	str = NULL;
	while (1)
	{
		if (buffer == NULL)
		{
			buffer = malloc(BUFFER_SIZE);
			if (buffer == NULL)
				return (NULL);
			bytesread = read(fd, buffer, BUFFER_SIZE);
			if (bytesread <= 0)
				return (NULL);
			k = 0;
		}
		else
		{
			bytesread = ft_strlen(buffer);
			k = 1;
		}
		tmp = malloc(bytesread);
		if (tmp == NULL)
			return (NULL);
		if (str == NULL)
		{
			str = malloc(bytesread);
			if (str == NULL)
				return (NULL);
		}
		while (i < bytesread)
		{
			if (buffer[i] == '\n')
			{
				i++;
				break ;
			}
			tmp[i] = buffer[i];
			i++;
			if (i + 1 == bytesread)
				tmp[i] = '\0';
		}
		if (i == bytesread && i < BUFFER_SIZE && ft_strchr(buffer, '\n') == NULL)
			buffer[bytesread] = '\0';
		if (i == bytesread)
		{
			str_old = str;
			str = ft_strjoin(str_old, tmp);
			if (str == NULL)
				return (NULL);
			buffer = NULL;
			if (k == 0 && i < BUFFER_SIZE && i == bytesread)
				break ;
			i = 0;
			tmp = NULL;
			free(tmp);
			free(str_old);
		}
		else if (i < bytesread)
		{
			j = 0;
			if (tmp != NULL)
			{
				str_old = str;
				str = ft_strjoin(str_old, tmp);
			}
			if (str == NULL)
				return (NULL);
			while (i < bytesread)
			{
				buffer[j] = buffer[i];
				i++;
				j++;
			}
			while (j < bytesread)
			{
				buffer[j] = 0;
				j++;
			}
			break ;
		}
	}
	free(tmp);
	free(str_old);
	return (str);
}
/*
int main()
{
	int		fd;
	char	*line;
	int		i;

	i = 15;
	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while (i > 0)
	{
		line = get_next_line(fd);
		printf("FINAL: %s\n", line);
		free(line);
		i--;
	}
	close(fd);
	return(0);
}
*/