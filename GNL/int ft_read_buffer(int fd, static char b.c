int ft_read_buffer(int fd, static char buffer)
{
    int     bytesRead;
    
    bytesRead = read(fd, buffer, BUFFER_SIZE);
    if (bytesRead <= 0)
        return (NULL);
    
    
}

char    *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static  int index;
    char        *str = NULL;
    int         i;
    
    while (buffer[i] != '\\' && buffer[i + 1] != 'n')
    {
        buffer = ft_read_buffer(fd, buffer);
        i = 0;
        while (i != BUFFER_SIZE)
        {
            ft_putchar(buffer[i]);
            i++;
        }   
    }
    return (NULL);
}








if (i < bytesRead)
{
    str = ft_strdup(buffer + index);
    index = i + 1;
    return (str);
}
if (i == bytesRead)
{    
    index = 0;
    return (ft_strdup(buffer));
}