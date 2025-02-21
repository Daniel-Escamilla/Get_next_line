# Get_next_line

Get Next Line una función en C que permite leer un archivo línea por línea a través de un file descriptor. Su implementación gestiona correctamente la memoria y permite leer tanto archivos como la entrada estándar.

## 📥 Clonación del repositorio
 
Para obtener una copia local del proyecto, usa:
```sh
git clone https://github.com/Daniel-Escamilla/Get_next_line.git
cd Get_next_line
```

## ⚙️ Uso de la función

### 📌 Prototipo:
```c
char *get_next_line(int fd);
```

- `fd` → File descriptor desde el que se leerá la línea.
- Retorna la siguiente línea del archivo, o `NULL` si ha terminado la lectura o ha ocurrido un error.

### 📌 Ejemplo de uso:

Archivo `main.c`: 
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
 ### 🚀 Compilación 
  Para compilar un programa que use `get_next_line`, ejecuta:
```sh
gcc main.c get_next_line.c get_next_line_utils.c -o programa
```
Donde `main.c` es el archivo de prueba. 
### 📌 Notas importantes
- La función puede leer tanto archivos como `stdin`.
- Cada línea devuelta finaliza en `\n`, salvo la última si el archivo no termina en un salto de línea.
- Internamente usa `read`, `malloc` y `free` para la gestión de memoria.
- Se recomienda entender cómo funcionan las **variables estáticas** para optimizar la gestión de la lectura.