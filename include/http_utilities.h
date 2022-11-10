#ifndef HTTP_UTILITIES_H
#define HTTP_UTILITIES_H
void get_method(char *str, char *buffer, int buffer_size);
void get_resource(char *str, char *buffer, int buffer_size);

void get_method(char *str, char *buffer, int buffer_size)
{
    int i = 0;
    while( str[i] != ' ' && str[i] != '\0' && i < buffer_size) {
        buffer[i] = str[i];
        ++i;
    }
    buffer[i] = '\0';
}

void get_resource(char *str, char *buffer, int buffer_size)
{
    int i = 0;
    int j = 0;
    while(str[i++] != ' ' && str[i] != '\0' && i < buffer_size)
        ;
    while( str[i] != ' ' && str[i] != '\0' && i < buffer_size) {
        buffer[j++] = str[i];
        ++i;
    }
    buffer[j] = '\0';
}

#endif //HTTP_UTILITIES_H
