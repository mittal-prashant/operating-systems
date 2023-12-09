#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("ERROR : Input/Output file name not passed as parameter.\n");
        return 1;
    }
    int file[2];
    pid_t child_id;
    if (pipe(file) == -1)
    {
        printf("Pipe failed.\n");
        return 1;
    }
    int input_file = open(argv[1], O_RDONLY);
    int output_file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (input_file == -1 || output_file == -1)
    {
        printf("Unable to open Input/Output file.\n");
        return 1;
    }
    int size = 50;
    char *read_msg = (char *)calloc(50, sizeof(char));
    child_id = fork();
    if (child_id < 0)
    {
        printf("Fork Failed.\n");
        return 1;
    }
    else if (child_id == 0)
    {
        close(file[1]);
        int read_size = read(file[0], read_msg, size);
        while (read_size)
        {
            write(output_file, read_msg, read_size);
            read_size = read(file[0], read_msg, size);
        }
        close(file[0]);
        close(output_file);
    }
    else
    {
        close(file[0]);
        int read_size = read(input_file, read_msg, size);
        while (read_size)
        {
            write(file[1], read_msg, read_size);
            read_size = read(input_file, read_msg, size);
        }
        close(file[1]);
        close(input_file);
    }
    return 0;
}
