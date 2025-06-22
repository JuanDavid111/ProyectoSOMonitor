#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include "utilidades_config.h"

int main(){
    Appconfig config;
    openlog("PROYECTO_SO1_DAEMON", LOG_PID | LOG_CONS, LOG_DAEMON);

    crear_directorio_log();
    crear_directorio_config();
    if(verificar_archivo_ini() != 0){
        closelog();
        exit(EXIT_FAILURE);
    }

    obtener_info_config(&config);

    closelog();
    return 0;
}