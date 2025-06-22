#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<errno.h>
#include<syslog.h>

#define ARCHIVO_CONFIG "/etc/proyecto so 1/proy1.ini"
#define LOG_DIR "/var/log/PROYECTO SO 1"
#define CONFIG_DIR "/etc/proyecto so 1"


int crear_directorio_config(){
    struct stat st;

    if(stat(CONFIG_DIR, &st) != 0){ //Si ya existe, no lo crea
        if(mkdir(CONFIG_DIR, 0755) == 0) {
                return 0;
        }
    }
}

int crear_directorio_log(){
    struct stat st;

    if(stat(LOG_DIR, &st) != 0){ //Si ya existe, no lo crea
        if(mkdir(LOG_DIR, 0755) == 0) {
                return 0;
        }
    }
}

int verificar_archivo_ini(){
    if(access(ARCHIVO_CONFIG, F_OK) == 0){ 
        return 0; //Archivo encontrado
    }else{ //Archivo No encontrado
        syslog(LOG_ERR, "ERROR: Archivo config no existe.");
        return -1; 
    }
}

int main(){
    openlog("PROYECTO_SO1_DAEMON", LOG_PID | LOG_CONS, LOG_DAEMON);

    crear_directorio_log();
    crear_directorio_config();
    if(verificar_archivo_ini() != 0){
        closelog();
        exit(EXIT_FAILURE);
        return 0;
    }

    syslog(LOG_INFO, "Aplicación daemon iniciada y procesando...");

    closelog();
}
