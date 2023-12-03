/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Esquema.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:46:44 by descamil          #+#    #+#             */
/*   Updated: 2023/11/27 17:27:54 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_buffer_move(char *buffer, int i, int j, char *tmp)
{
	if ((ft_strchr(buffer, '\n') == 1 || ft_strchr(buffer, '\0') == 1)
		&& i < ft_strlen(buffer))
	{
		while ((buffer[i] != '\0' && buffer[i] != '\n')
			&& i < ft_strlen(buffer))
		{
			tmp[i] = buffer[i];
			i++;
		}
		if (buffer[i] == '\n')
			tmp[i++] = '\n';
		tmp[i] = '\0';
	}
	while (i < BUFFER_SIZE)
		buffer[j++] = buffer[i++];
	while (j < i)
		buffer[j++] = '\0';
	return (buffer);
}

char	*ft_read(int fd, char *buffer)
{
	int	bytes_read;

	buffer = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (buffer == NULL)
	{
		free (buffer);
		buffer = NULL;
		return (NULL);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free (buffer);
		buffer = NULL;
		return (NULL);
	}
	if (bytes_read == 0)
	{
		free(buffer);
		buffer = NULL;
	}
	if (buffer != NULL)
		buffer[bytes_read] = '\0';
	return (buffer);
}

char	*ft_buffer_extract(char *buffer, char *line)
{
	char	*tmp;

	tmp = NULL;
	if (buffer == NULL)
		return (line);
	tmp = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	buffer = ft_buffer_move(buffer, 0, 0, tmp);
	line = ft_strjoin(line, tmp);
	if (buffer)
	{
		if (buffer[0] == '\0')
			buffer = NULL;
	}
	free (tmp);
	tmp = NULL;
	return (line);
}

char	*ft_first_line(char *buffer, int fd)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while (1)
	{
		if (ft_strchr(buffer, '\n') == 1)
			break ;
		else if ((ft_strlen(buffer) < BUFFER_SIZE
				&& ft_strchr(buffer, '\n') == 0) || BUFFER_SIZE == 1 || i == 1)
		{
			i = 0;
			line = ft_strjoin(line, buffer);
			if (buffer != NULL)
			{
				free(buffer);
				buffer = NULL;
			}
			buffer = ft_read(fd, buffer);
			if (buffer == NULL)
			{
				free(buffer);
				break ;
			}
		}
		if ((ft_strlen(buffer) < BUFFER_SIZE
				&& (ft_strchr(buffer, '\n') == 0)))
			break ;
		i++;
	}
	line = ft_buffer_extract(buffer, line);
	if (buffer)
	{
		if (buffer[0] == '\0')
		{
			free(buffer);
			buffer = NULL;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			i;
	int			j;

	i = 0;
	j = 0;
	line = NULL;
	if (buffer)
	{
		if (buffer[0] == '\0' || BUFFER_SIZE == 1)
			buffer = NULL;
	}
	if (!buffer)
	{
		buffer = ft_read(fd, buffer);
		if (buffer == NULL)
			return (NULL);
		line = ft_first_line(buffer, fd);
	}
	else
		line = ft_first_line(buffer, fd);
	if (buffer == NULL)
		return (line);
	if (line == NULL)
	{	
		free(line);
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (line);
}


// void runleaks(void)
// {
//    system("leaks a.out");
// }

int main()
{
	int		fd;
	char	*line;
	int		i;

	i = 2;
	fd = open("lines_around_10.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while (i > 0)
	{
		line = (get_next_line(fd));
		printf("%s",line);
		free(line);
		i--;
	}
	// atexit(runleaks);
	close (fd);
	return (0);
}
