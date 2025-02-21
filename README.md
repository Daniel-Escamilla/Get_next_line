# Get_next_line

Get Next Line una función en C que permite leer un archivo línea por línea a través de un file descriptor. Su implementación gestiona correctamente la memoria y permite leer tanto archivos como la entrada estándar.

## 📥 Clonación del repositorio

```sh
git clone https://github.com/Daniel-Escamilla/Get_next_line.git
cd Get_next_line
```

## 🚀 Uso de la función

### 📌 Ejemplo de uso:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	char	*line;
	int		fd;

	fd = open("archivo.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```
## ⚙️ Compilación 

```sh
gcc main.c get_next_line.c get_next_line_utils.c -o programa
```

## 📌 Notas importantes

- La función puede leer tanto archivos como `stdin`.
- Cada línea devuelta finaliza en `\n`, salvo la última si el archivo no termina en un salto de línea.
- Internamente usa `read`, `malloc` y `free` para la gestión de memoria.
- Se recomienda entender cómo funcionan las **variables estáticas** para optimizar la gestión de la lectura.