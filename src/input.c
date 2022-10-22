#include "input.h"

FILE *open_file(const char *filename)
{
    FILE *file_ptr = fopen(filename, "r");

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
