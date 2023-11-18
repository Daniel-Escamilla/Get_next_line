#include <stdlib.h>

/*
	Primero trazamos una idea general de lo que tiene que hacerla función principal.
	A partir de ahi, vamos creando las funciones que hemos puesto, y vamos sacando
	conclusiones
*/

char	*get_next_line1(int fd)
{
	/*
		Creamos la variable estática, donde va a estar el extra de cada vez que leemos.
		Hacemos que sea un puntero para poder hacer malloc sobre él, ya que no sabemos cuanto
		espacio va a tener.
	*/
	static char	*buffer;

	/*
		Leemos y guardamos en buffer todo lo que teníamos + lo que acabamos de leer. Vamos
		a leer hasta la función 'read':
			- Devuelva un número negativo --> Error al leer
			- Devuelva 0 --> hemos llegado al final del archivo
			- Una vez leido, encontramos algún '\n' en buffer --> Hay (mínimo) una linea
	*/
	buffer = leer_de_archivo(fd, buffer);

	/*
		Ahora mismo en buffer se encuentra todo el texto de la anterior vez que se llamó al gnl +
		todo lo que acabamos de leer. Por ello, podemos extraer línea.
		En el caso en el que no haya un '\n', todo lo que haya en 'buffer' es la línea
	*/
	char *line;
	line = guardar_primera_linea(buffer);

	/*
		Como en 'line' ya tengo la primera línea, actualizo 'buffer' para que desaparezca.
		Si el primer caracter de la nueva string es '\0', podemos eliminarlo, ya que no nos
		hace falta una string sin información (todo lo que teníamos era la linea)
	*/
	buffer = eliminar_linea(buffer);

	/* Devolvemos la línea*/
	return (line);
}

/*
	Viendo todos los comentarios de antes, podemos añadir test de errores
*/
char	*get_next_line2(int fd)
{
	char *line;
	static char *buffer;

	/* Podemos hacer que buffer devuelva NULL si hay algún error de lectura o malloc*/
	buffer = leer_de_archivo(fd, buffer);
	if (!buffer)
		return (NULL);
	
	/* Si hay problema al extraer la linea (malloc problem), eliminar todo */
	line = guardar_primera_linea(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}

	/*
		Al igual que antes, si hay algun problema al actualizar buffer devolvemos NULL.
		La función deberia liberar la memoria de 'buffer' si hay error
	*/
	buffer = eliminar_linea(buffer);
	if (!buffer)
		return (NULL);

	return (line);
}


/*
	Nos podemos platear el caso en el que, al leer, leemos 2 lineas. En este caso, las funciones
	'guardar_primera_linea' y 'eliminar_linea' actualizaran eliminar la primera linea, no el resto,
	osea que antes de devolver la linea tendremos en buffer más líneas.
	Por ello, al entrar a la funciñon del gnl la próxima vez podríamos comprobar si ya existe una
	linea, y así nos libramos de leer otra vez innecesariamente
*/
char	*get_next_line3(int fd)
{
	char *line;
	static char *buffer;

	/* Si hay algún '/n', guardamos la linea y actualizamos 'buffer' */
	if (existe_caracter(buffer, '\n'))
	{
		line = guardar_primera_linea(buffer);
		// Test de errores

		buffer = eliminar_linea(buffer);
		// Test de errores

		return (line);
	}

	buffer = leer_de_archivo(fd, buffer);
	if (!buffer)
		return (NULL);
	
	line = guardar_primera_linea(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}

	buffer = eliminar_linea(buffer);
	if (!buffer)
		return (NULL);

	return (line);
}

/* Ahora solo falta crear las funciones
	- 'existe_caracter'
	- 'leer_de_archivo'
	- 'guardar_primera_linea'
	- 'eliminar_linea'
	, además de las subfunciones que necesiten (get_next_line_utils.c)
*/