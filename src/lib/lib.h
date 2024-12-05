#ifndef LIB_H
#define LIB_H

    #include <netinet/in.h>

    #define PORT 6969
    #define IP INADDR_ANY // Como estamos rodando localmente, a constante INADDR_ANY está no servidor e cliente

    #define BUFFER_SIZE 1024

    void clean_buffer(char buffer[]){
        for(int i = 0; i < BUFFER_SIZE; i++){
            buffer[i] = '\0';
        }
    }

#endif

