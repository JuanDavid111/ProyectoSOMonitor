#ifndef EMPAQUETADOR_H
#define EMPAQUETADOR_H

#include <stdint.h>

#define MAX_PATH_LEN 512
#define MAX_FILES 1024

typedef struct {
    char ruta_completa[MAX_PATH_LEN];
    char nombre_truncado[32];
    uint64_t tamano_bytes;
} ArchivoEmpaquetable;

extern ArchivoEmpaquetable archivosEmpaquetables[MAX_FILES];
extern int cantidadEmpaquetables;

//void empaquetar_archivos(ArchivoEmpaquetable archivos[], int cantidad);

#endif
