#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        write(2, "Error : Very Few Arguments\n", sizeof("Error : Very Few Arguments\n"));
        exit(1);
    }
    if (argc > 3)
    {
        write(2, "Error : Extra Arguments\n", sizeof("Error : Extra Arguments\n"));
        exit(1);
    }
    char *file1 = argv[1]; // Give the first argument as input.txt which is already created or create a file and then give the file name as argument
    char *file2 = argv[2];
    int fd1 = open(file1, O_RDONLY);
    int fd2 = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 < 0)
    {
        write(2, "Error : Opening Source File\n", sizeof("Error : Opening Source File\n"));
        exit(1);
    }
    if (fd2 < 0)
    {
        write(2, "Error : Creating Destination File\n", sizeof("Error : Creating Destination File\n"));
        exit(1);
    }
    char *c = (char *)calloc(100, sizeof(100));
    int sz;
    while (sz = read(fd1, c, 100))
    {
        write(fd2, c, sz);
    }
    if (close(fd1) < 0)
    {
        write(2, "Error : Closing Source File\n", sizeof("Error : Closing Source File\n"));
        exit(1);
    }
    if (close(fd2) < 0)
    {
        write(2, "Error : Closing Destination File\n", sizeof("Error : Closing Destination File\n"));
        exit(1);
    }
    return 0;
}
