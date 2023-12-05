/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:40:35 by descamil          #+#    #+#             */
/*   Updated: 2023/12/05 19:43:24 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*ft_buffer_move(char *buffer, int i, int j, char *tmp)
// {
// 	if ((ft_strchr(buffer, '\n') == 1)
// 		&& i < ft_strlen(buffer))
// 	{
// 		while ((buffer[i] != '\0' && buffer[i] != '\n')
// 			&& i < ft_strlen(buffer))
// 		{
// 			tmp[i] = buffer[i];
// 			i++;
// 		}
// 		if (buffer[i] == '\n')
// 			tmp[i++] = '\n';
// 		tmp[i] = '\0';
// 	}
// 	while (i < BUFFER_SIZE)
// 		buffer[j++] = buffer[i++];
// 	while (j < i)
// 		buffer[j++] = '\0';
// 	return (buffer);
// }

// char	*ft_read(int fd, char *buffer)
// {
// 	int	bytes_read;

// 	buffer = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
// 	if (buffer == NULL)
// 		return (NULL);
// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	if (bytes_read < 0)
// 	{
// 		free (buffer);
// 		buffer = NULL;
// 		return (NULL);
// 	}
// 	if (bytes_read == 0)
// 	{
// 		free(buffer);
// 		buffer = NULL;
// 	}
// 	return (buffer);
// }

// char	*ft_buffer_extract(char *buffer, char *line)
// {
// 	char	*tmp;

// 	tmp = NULL;
// 	if (buffer == NULL)
// 		return (line);
// 	tmp = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
// 	if (!tmp)
// 		return (NULL);
// 	buffer = ft_buffer_move(buffer, 0, 0, tmp);
// 	line = ft_strjoin(line, tmp);
// 	if (buffer)
// 	{
// 		if (buffer[0] == '\0')
// 			buffer = NULL;
// 	}
// 	free (tmp);
// 	return (line);
// }

// char	*ft_first_line(char *buffer, int fd, int i)
// {
// 	char	*line;

// 	line = NULL;
// 	while (1)
// 	{
// 		if (!buffer)
// 		{
// 			buffer = ft_read(fd, buffer);
// 			if (buffer == NULL)
// 				break ;
// 		}
// 		if (ft_strchr(buffer, '\n') == 1)
// 			break ;
// 		else if (ft_strchr(buffer, '\n') == 0 
// 				&& ft_strlen(buffer) < BUFFER_SIZE && i == 0)
// 			break ;
// 		else
// 		{
// 			line = ft_strjoin(line, buffer);
// 			if (buffer != NULL)
// 			{
// 				free(buffer);
// 				buffer = NULL;
// 			}
// 		}
// 	}
// 	line = ft_buffer_extract(buffer, line);
// 	if (buffer && buffer[0] == '\0')
// 	{
// 		free(buffer);
// 		buffer = NULL;
// 	}
// 	return (line);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*buffer;
// 	char		*line;

// 	if (fd < 0 || read(fd, NULL, 0))
// 	{
// 		if(buffer)
// 			free(buffer);
// 		buffer = NULL;
// 		return NULL;
// 	}

// 	line = NULL;
// 	if ((buffer && buffer[0] == '\0') || BUFFER_SIZE == 1)
// 		buffer = NULL;
// 	if (!buffer)
// 	{
// 		buffer = ft_read(fd, buffer);
// 		if (buffer == NULL)
// 			return (NULL);
// 		line = ft_first_line(buffer, fd, 0);
// 	}
// 	else
// 		line = ft_first_line(buffer, fd, 1);
// 	if (line == NULL)
// 	{
// 		if (buffer)
// 			free(buffer);
// 		buffer = NULL;
// 		return (NULL);
// 	}
// 	if (buffer && ft_strchr(line, '\n') == 0)
// 	{
// 		buffer = NULL;
// 		return (line);
// 	}
// 	return (line);
// }

char	*read_l(int fd, char *buffer)
{
	char	aux[BUFFER_SIZE + 1];
	int		bytes_read;

	while (1)
	{
		if (buffer && buffer[0] == '\0')
			buffer = NULL;
		bytes_read = read(fd, aux, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		aux[bytes_read] = '\0';
		if (aux[0] == '\0')
			return (buffer);
		buffer = ft_strjoin(buffer, aux);
		if (!buffer)
			return (NULL);
		if (bytes_read != BUFFER_SIZE || ft_strchr(buffer, '\n'))
			return (buffer);
	}
	return (NULL);
}

char	*extraer_linea(char *buffer)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*delete_line(char *buffer)
{
	char	*new;
	int		i;
	int		j;

	new = NULL;
	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	i++;
	new = ft_calloc(ft_strlen(buffer) - i + 1, 1);
	if (!new)
	{
		free(buffer);
		free(new);
		return (NULL);
	}
	j = 0;
	while (buffer[i])
		new[j++] = buffer[i++];
	free(buffer);
	buffer = NULL;
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0)
		return (NULL);
	buffer = read_l(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extraer_linea(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = delete_line(buffer);
	if (buffer && buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
	}
	if (line && line[0] == '\0')
		line = NULL;
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		free(line);
	}
	return (line);
}

// void runleaks(void)
// {
//    system("leaks a.out");
// }

// int	main(void)
// {
// 	char	*line;
// 	int		fd;
// 	int		i;

// 	i = 50;
// 	fd = open("read_error.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	while (i > 0)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i--;
// 	}
// 	atexit(runleaks);
// 	close (fd);
// 	return (0);
// }

// int main()
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 2;
// 	fd = open("big_line_with_nl", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	while (i > 0)
// 	{
// 		line = (get_next_line(fd));
// 		printf("%s",line);
// 		free(line);
// 		i--;
// 	}
// 	// atexit(runleaks);
// 	close (fd);
// 	return (0);
// }