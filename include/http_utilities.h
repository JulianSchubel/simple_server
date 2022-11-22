#ifndef HTTP_UTILITIES_H
#define HTTP_UTILITIES_H

enum methods {
    GET = 0,
    POST,       /* Create/Update when exact resource location not known. I.e. determined by server. */
    PUT,        /* Create/Update when exact resource location known. I.e. determined by client user. Idempotent */
    DELETE,
    HEAD,
    NUM_METHODS
};

typedef struct record_t {
    char * key;
    int value;
} record_t;

record_t method_table[] = {
    {"GET", GET},
    {"POST", POST},
    {"PUT", PUT},
    {"DELETE", DELETE}
};

/* PROTOTYPES */
void get_method(char *str, char *buffer, int buffer_size);
void get_resource(char *str, char *buffer, int buffer_size);
int lookup_method(char * key, record_t * lookup_table, int table_size);

/* DEFINITIONS */
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

/* lookup: iterate over lookup table entries and return the integer value associated with a matching string */
int lookup_method(char * key, record_t * lookup_table, int table_size)
{
    for(int i = 0; i < table_size; ++i) {
        if(strcmp(lookup_table[i].key, key) == 0) {
            return lookup_table[i].value;
        }
    }
    return -1;
}

#endif //HTTP_UTILITIES_H
