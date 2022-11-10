#ifndef FILE_IO_UTILITIES_H
#define FILE_IO_UTILITIES_H

/* get_flen: get the size of an open file descriptor */
int get_flen(FILE * file);
/* get_fdata: store the contents of an open file descriptor in a character array; */
void get_fdata(char * buffer, FILE *file, int buffer_length);

/* get_flen: get the size of an open file descriptor */
int get_flen(FILE* stream)
{
    /* Get length of file by seeking to EOF */
    fseek(stream, 0L, SEEK_END);
    /* Number of characters is equal to the file position indicator */
    int data_length = ftell(stream);
    /* Set the file position indicator back to the start of the file */
    fseek(stream, 0L, SEEK_SET);
    return data_length;
}

/* get_fdata: store the contents of stream in buffer; */
void get_fdata(char* buffer, FILE* stream, int buffer_length)
{
    int i = 0;
    char c;
    while( (c = fgetc(stream)) != EOF && i < buffer_length)
    {
        buffer[i++] = c;
    }
    buffer[i] = '\0';
}

#endif //FILE_IO_UTILITIES_H
