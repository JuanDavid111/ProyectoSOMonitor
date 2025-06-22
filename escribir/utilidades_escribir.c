#include "utilidades_escribir.h"
#include <stdio.h>
#include <stdlib.h>

#define FILENAME "29615514_29611486_30667176.txt"

void registrar_PID(char *intervalo, int pid) {
    FILE *archivo = fopen(FILENAME, "a");

    if(intervalo == NULL){
        fprintf(archivo, "%d\n", pid);
    }else{
        fprintf(archivo, "%s %d\n", intervalo, pid);
    }

    fclose(archivo);
}