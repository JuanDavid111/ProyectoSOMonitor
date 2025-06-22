#ifndef UTILIDADES_CONFIG_H
#define UTILIDADES_CONFIG_H

#include <stdio.h>

#define ARCHIVO_CONFIG "/etc/proyecto so 1/proy1.ini"
#define LOG_DIR "/var/log/PROYECTO SO 1"
#define CONFIG_DIR "/etc/proyecto so 1"

typedef struct {
    char log_tag[128];
    int interval;
} Appconfig;

int crear_directorio_config();
int crear_directorio_log();
int verificar_archivo_ini();
char* limpiar_linea(char *linea);
int obtener_info_config(Appconfig *config);

#endif