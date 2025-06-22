#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <syslog.h>
#include "utilidades_config.h"

int crear_directorio_config(){
    struct stat st;

    if(stat(CONFIG_DIR, &st) != 0){ //Si ya existe, no lo crea
        if(mkdir(CONFIG_DIR, 0755) == 0){
                return 0;
        }
    }
    return 0;
}

int crear_directorio_log(){
    struct stat st;

    if(stat(LOG_DIR, &st) != 0){ // Si no existe, lo crea
        if(mkdir(LOG_DIR, 0755) == 0){
            return 0;
        }
    }
    return 0;
}

int verificar_archivo_ini(){
    if(access(ARCHIVO_CONFIG, F_OK) == 0){
        return 0; // Archivo encontrado
    }else{ // Archivo No encontrado
        syslog(LOG_ERR, "ERROR: Archivo de configuración no existe.");
        return -1;
    }
}

char* limpiar_linea(char *linea){
    char* fin_linea;

    while(isspace((unsigned char)*linea))linea++;
    fin_linea = linea + strlen(linea) - 1;
    while(fin_linea > linea && isspace((unsigned char)*fin_linea)) fin_linea--;

    *(fin_linea + 1) = 0;

    return linea;
}

int obtener_info_config(Appconfig *config){
    FILE *archivoINI = fopen(ARCHIVO_CONFIG, "r");

    char linea[256];
    int marcador_conf = 0;

    while(fgets(linea, sizeof(linea), archivoINI) != NULL){
        char *linea_limpia = limpiar_linea(linea);

        if(strlen(linea_limpia) == 0 || linea_limpia[0] == ';'){ // Salto de lineas en blanco y ; (comentarios)
            continue;
        }

        if(strcmp(linea_limpia, "[CONF]") == 0){ // Lee [CONF] y lo salta
            marcador_conf = 1;
            continue;
        }

        if(marcador_conf){ // Dentro de [CONF]
            char *key = linea_limpia;
            char *value = strchr(linea_limpia, '='); // Busca el signo =

            if(value != NULL){ // quita el =
                *value = '\0';
                value++;

                if(strcmp(key, "log_tag") == 0){
                    strncpy(config->log_tag, value, sizeof(config->log_tag) - 1);
                    config->log_tag[sizeof(config->log_tag) - 1] = '\0';
                }else if(strcmp(key, "interval") == 0){
                    config->interval = atoi(value);
                }
            }
        }
    }

    fclose(archivoINI);
    return 0;
}