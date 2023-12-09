#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    int fd = open("text.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        write(2, "Error : Opening File\n", sizeof("Error : Opening File\n"));
        exit(1);
    }
    char str[] = "Prashant Mittal\n";
    write(fd, str, sizeof(str));
    if (close(fd) < 0)
    {
        write(2, "Error : Closing File\n", sizeof("Error : Closing File\n"));
        exit(1);
    }
    fd = open("text.txt", O_RDONLY);
    if (fd < 0)
    {
        write(2, "Error : Opening File\n", sizeof("Error : Opening File\n"));
        exit(1);
    }
    char *c = (char *)calloc(100, sizeof(char));
    write(1, c, read(fd, c, 100));
    if (close(fd) < 0)
    {
        write(2, "Error : Closing File\n", sizeof("Error : Closing File\n"));
        exit(1);
    }
    return 0;
}
