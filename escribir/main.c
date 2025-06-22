#include <stdio.h>
#include <stdlib.h>
#include "utilidades_escribir.h"

int main() {

    registrar_PID(NULL, 1234);
    registrar_PID("intervalo",0);   
    registrar_PID(NULL, 5678);
    registrar_PID(NULL, 9101);

    registrar_PID("intervalo",1); 
    registrar_PID(NULL, 1121); 
    registrar_PID(NULL, 3141); 

    registrar_PID(NULL, 7777); 
    registrar_PID(NULL, 8888);
    registrar_PID("intervalo",2);       

    return 0;
}