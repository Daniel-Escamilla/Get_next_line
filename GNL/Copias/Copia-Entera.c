/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Copia-Entera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:00:56 by descamil          #+#    #+#             */
/*   Updated: 2023/11/27 17:00:57 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


	// /*
	// 	Primero trazamos una idea general de lo que tiene que hacer la función principal.
	// 	A partir de ahi, vamos creando las funciones que hemos puesto, y vamos sacando
	// 	conclusiones
	// */

	// char	*get_next_line1(int fd)
	// {
	// 	/*
	// 		Creamos la variable estática, donde va a estar el extra de cada vez que leemos.
	// 		Hacemos que sea un puntero para poder hacer malloc sobre él, ya que no sabemos cuanto
	// 		espacio va a tener.
	// 	*/
	// 	static char	*buffer;

	// 	/*
	// 		Leemos y guardamos en buffer todo lo que teníamos + lo que acabamos de leer. Vamos
	// 		a leer hasta la función 'read':
	// 			- Devuelva un número negativo --> Error al leer
	// 			- Devuelva 0 --> hemos llegado al final del archivo
	// 			- Una vez leido, encontramos algún '\n' en buffer --> Hay (mínimo) una linea
	// 	*/
	// 	buffer = ft_read(fd, buffer);

	// 	/*
	// 		Ahora mismo en el buffer se encuentra todo el texto de la anterior vez que se llamó al gnl +
	// 		todo lo que acabamos de leer. Por ello, podemos extraer línea.
	// 		En el caso en el que no haya un '\n', todo lo que haya en 'buffer' es la línea
	// 	*/
	// 	char *line;
	// 	line = ft_first_line(buffer);

	// 	/*
	// 		Como en 'line' ya tengo la primera línea, actualizo 'buffer' para que desaparezca.
	// 		Si el primer caracter de la nueva string es '\0', podemos eliminarlo, ya que no nos
	// 		hace falta una string sin información (todo lo que teníamos era la linea)
	// 	*/
	// 	buffer = ft_delete_line(buffer);

	// 	/* Devolvemos la línea*/
	// 	return (line);
	// }

	// /*
	// 	Viendo todos los comentarios de antes, podemos añadir test de errores
	// */
	// char	*get_next_line2(int fd)
	// {
	// 	char *line;
	// 	static char *buffer;

	// 	/* Podemos hacer que buffer devuelva NULL si hay algún error de lectura o malloc*/
	// 	buffer = ft_read(fd, buffer);
	// 	if (!buffer)
	// 		return (NULL);
		
	// 	/* Si hay problema al extraer la linea (malloc problem), eliminar todo */
	// 	line = ft_first_line(buffer);
	// 	if (!line)
	// 	{
	// 		free(buffer);
	// 		buffer = NULL;
	// 		return (NULL);
	// 	}

	// 	/*
	// 		Al igual que antes, si hay algun problema al actualizar buffer devolvemos NULL.
	// 		La función deberia liberar la memoria de 'buffer' si hay error
	// 	*/
	// 	buffer = ft_delete_line(buffer);
	// 	if (!buffer)
	// 		return (NULL);

	// 	return (line);
	// }


	// /*
	// 	Nos podemos plantear el caso en el que, al leer, leemos 2 lineas. En este caso, las funciones
	// 	'ft_first_line' y 'ft_delete_line' actualizaran eliminar la primera linea, no el resto,
	// 	osea que antes de devolver la linea tendremos en buffer más líneas.
	// 	Por ello, al entrar a la funciñon del gnl la próxima vez podríamos comprobar si ya existe una
	// 	linea, y así nos libramos de leer otra vez innecesariamente
	// */


char	*ft_read(int fd, char *buffer, char *line)
{
	int	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);								// Asigno memoria al buffer
	if (buffer == NULL)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (NULL);
	if (bytes_read == 0)
		return (line);
	buffer[bytes_read] = '\0';
	return (buffer);
}

char	*ft_buffer_extract(char *buffer, char *line, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = (char *)ft_calloc(sizeof(char *), BUFFER_SIZE + 1);
	if (ft_strchr(buffer, '\n') == 1)
	{
		while (buffer[i] != '\n')
		{
			tmp[i] = buffer[i];
			i++;
		}
		tmp[i++] = '\n';
		tmp[i] = '\0';
	}
	else if (ft_strchr(buffer, '\0') == 1)
	{
		while (buffer[i] != '\0')
		{
			tmp[i] = buffer[i];
			i++;
		}
		while (i < BUFFER_SIZE)
			tmp[i++] = '\0';
	}
	line = ft_strjoin(line, tmp);
	while (i < BUFFER_SIZE)
		buffer[j++] = buffer[i++];
	while (j < i)
		buffer[j++] = '\0';
	if (buffer[0] == '\0')
		buffer = NULL;
	free (tmp);
	tmp = NULL;
	return (line);
}

char	*ft_first_line(char *buffer, int fd)
{
	char	*line;
	int		i;

	line = NULL;
	while (1)
	{
		i = 0;
		if (ft_strlen(buffer) < BUFFER_SIZE)
		{
			line = ft_buffer_extract(buffer, line, i);
			break ;
		}
		if (ft_strchr(buffer, '\n') == 1)
		{
			line = ft_buffer_extract(buffer, line, i);
			break ;
		}
		else if (ft_strlen(buffer) < BUFFER_SIZE && ft_strchr(buffer, '\n') == 0)
		{
			line = ft_strjoin(line, buffer);
			free(buffer);
			buffer = ft_read(fd, buffer, line);
			if (!buffer)
				return (NULL);
		}
		if (ft_strlen(buffer) < BUFFER_SIZE && ft_strchr(buffer, '\n') == 0)
		{
			line = ft_buffer_extract(buffer, line, i);
			break ;
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
	if (!buffer)
	{
		buffer = ft_read(fd, buffer, line);
		if (!buffer)
			return (NULL);
		line = ft_first_line(buffer, fd);
		if (!line)
		{
			ft_clean_buffer(buffer);
			return (NULL);	
		}
	}
	else
	{
		while (ft_strchr(buffer, '\n') == 1 && buffer[i] != '\n')
		{
			if (i + 1 == ft_strlen(buffer))
				break ;			
			i++;
		}
		while (i < BUFFER_SIZE)
			buffer[j++] = buffer[i++];
		while (j < i)
			buffer[j++] = '\0';
		line = ft_first_line(buffer, fd);
		if (!line)
		{
			ft_clean_buffer(buffer);
			return (NULL);	
		}
		if (ft_strchr(line, '\n') == 0)
		{
			buffer = NULL;				// ft_clean_buffer(buffer);
		}
	}
	/* Si hay algún '/n' en el buffer, guardamos la linea y actualizamos 'buffer' */
	// if (ft_strchr(buffer, '\n') == 1)
	// {
	// 	line = ft_first_line(buffer);
	// 	if (!line)
	// 		return (ft_clean_buffer(&buffer));
	// 	buffer = ft_delete_line(buffer);
	// 	if (!buffer)
	// 		return (NULL);
	// 	return (line);
	// }
	// if (!buffer)
	// 	return (NULL);
	// buffer = ft_delete_line(buffer);
	// if (!buffer)
	// 	return (NULL);
	return (line);
}

void	ft_clean_buffer(char *buffer)
{
	free(buffer);
	buffer = NULL;
}

/* Ahora solo falta crear las funciones
	- 'ft_read' == ft_read()
	- 'ft_first_line' == ft_first_line()
	- 'ft_delete_line' == ft_delete_line()
	, además de las subfunciones que necesiten (get_next_line_utils.c)
*/

// int main()
// {
// 	int		fd;
// 	char	*line;
// 	int		i;
	
// 	i = 90;
// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	while (i > 0)
// 	{
// 		line = (get_next_line(fd));
// 		printf("%s", line);
// 		free (line);
// 		i--;
// 	}
// 	close (fd);
// 	return (0);
// }
