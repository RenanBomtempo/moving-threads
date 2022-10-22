#include "input.h"

FILE *open_file(const char *filename, const char *mode)
{
    FILE *file_ptr = fopen(filename, mode);

    if (!file_ptr)
    {
        printf("Could not open file.\n");
        exit(-1);
    }

    DEBUG_LOG("File opened succesfully!\n");

    return file_ptr;
}

void close_file(FILE *file)
{
    fclose(file);
}
