/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:00:27 by descamil          #+#    #+#             */
/*   Updated: 2023/11/18 18:41:47 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*ft_buffer(int fd, char *buffer)
// {
// 	int	bytesread; 

// 	buffer = malloc(BUFFER_SIZE + 1);
// 	if (buffer == NULL)
// 		return (NULL);
// 	bytesread = read(fd, buffer, BUFFER_SIZE);
// 	if (bytesread < 0)
// 		return (NULL);
// 	if (bytesread >= 0)
// 	{
// 		if (bytesread > 0)
// 			buffer[BUFFER_SIZE + 1] = '\0';
// 	}
// 	return (buffer);
// }

char	*ft_memcpy(char *dst, char *src, int num)
{
	int			i;

	if (src == NULL && dst == NULL)
		return (NULL);
	dst = (char *)malloc(num);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < num)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

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
		if (buffer == NULL)											// En el caso de que buffer esté vacio
		{
			buffer = (char *)malloc(BUFFER_SIZE + 1);								// Asigno memoria al buffer
			if (buffer == NULL)
				return (NULL);
			bytesread = read(fd, buffer, BUFFER_SIZE);						// Le doy el contenido de lo que lee
			if (bytesread < 0)
				return (NULL);
			buffer[bytesread + 1] = '\0';									// Le pongo '\0' al final para poder iterar
			k = 0;
			tmp = (char *)malloc(bytesread + 1);									// Asigno memoria a tmp para que entre el buffer
			if (tmp == NULL)
				return (NULL);
		}
		else if (buffer != NULL)									// En caso de que el buffer tenga contenido
		{
			// * [if (ft_strchr(tmp, '\n') == 0)] * //
			if (ft_strchr(buffer, '\n') == 0)							// Si no hay saltos de linea en tmp
			{
				tmp = ft_memcpy(tmp, buffer, ft_strlen(buffer) + 1);			// Copiamos el contenido del buffer en el tmp
				bytesread = read(fd, buffer, BUFFER_SIZE);					// Cogemos nuevo contenido
				while (i < bytesread && buffer[i] != '\n')					// Hasta que llegue al primer '\n'
				{
					tmp[ft_strlen(tmp) + i] = buffer[i];					// Copiamos el contenido nuevo en el tmp
					i++;
				}
				i++;
				while (i < bytesread)										// Si despues del '\n' hay más contenido
					buffer[j++] = buffer[i++];								// Se copia en el mismo buffer para que vuelva arriba
				while (j < i)
					buffer[j++] = '\0';
			}
			else													// Si hay saltos de liena en tmp
			{
				tmp = NULL;
				bytesread = ft_strlen(buffer);									// Asignamos el tamaño de tmp
				while (buffer[i] != '\n')										// Buscamos el salto de linea
					i++;
				tmp = (char *)malloc(i + 1);							// Asgnamos memoria a str_old
				if (tmp == NULL)
					return(NULL);
				i = 0;
				while (buffer[i] != '\n')										// Mientras que no se encuentre el salto de linea
				{
					tmp[i] = buffer[i];									// Copio los valores antes del salto de linea
					i++;
				}
				i++;														// Saltamos el salto de linea
				while (buffer[i] != '\0')
					buffer[j++] = buffer[i++];									// Si quedan más caracteres, los despazo hacia delante
				while (j < i)
					buffer[j++] = '\0';										// El espacio sobrante, los sustituyo por '\0'
			}
		}
		if (str == NULL)											// Combrobamos que str es NULL o k es 1
		{
			str = (char *)malloc(bytesread + ft_strlen(buffer) + 1);		// Damos memoria a str
			if (str == NULL)
				return (NULL);
		}
		if (tmp != NULL)											// Si tmp tiene memoria creada
		{
			while (i < bytesread)
			{
				tmp[i] = buffer[i];											// Copiamos los datos del buffer en tmp
				if (buffer[i] == '\n')										// Buscamos el salto de linea
				{
					i++;
					break ;
				}
				i++;
			}
		}
		if (ft_strchr(buffer, '\0') == 0)											// Si el salto de linea está al final
		{
			str_old = str;													// Asignamos el contenido de str en str_old
			str = ft_strjoin(str_old, tmp);									// Juntamos las cadenas str_old y tmp en lla cadena str
			if (str == NULL)
				return (NULL);
			i = 0;
			buffer = NULL;
			tmp = NULL;														// Reiniciamos los valores
			str_old = NULL;
			free(tmp);															
			free(str_old);
		}
		else if (ft_strchr(buffer, '\n' == 1))										// Si el salto de linea no esta al final
		{
			j = 0;
			if (tmp != NULL)												// Si tmp tiene contenido
			{
				str_old = str;
				str = ft_strjoin(str_old, tmp);								// Juntamos el contenido de str_old con tmp en str
			}
			if (str == NULL)
				return (NULL);
			if (i < bytesread)
			{
				while (i < bytesread)											// Si quedan más caracteres, los despazo hacia delante
					buffer[j++] = buffer[i++];
				while (j <= bytesread)											// El espacio sobrante, los sustituyo por '\0'
					buffer[j++] = '\0';
			}
			if (str != NULL && ft_strchr(str, '\n') == 0)			// Si str no es NULL y no tine un salto de linea
				str[ft_strlen(str)] = '\n';									// Se le añade uno
			tmp = NULL;
			str_old = NULL;
			free(tmp);														// Reiniciamos valores
			free(str_old);
			break ;															// Salimos del while
		}
	}
	return (str);													// Devolvemos la cadena final
}

int main()
{
	int		fd;
	char	*line;
	int		i;

	i = 3;
	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while (i > 0)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i--;
	}
	close(fd);
	return(0);
}
/*
	- Poner \0 despues de read, sino no puedes iterar
	- No miras que al empezar la función la static ya tenga contenido. En este caso, deberías revisar si ya existe una linea
	- Hazte un esquema de como lo quieres estructurar antes, a lo mejor te ayuda
*/