#include "empaquetador.h"
#include "comprimir/comprimir_utilidades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void empaquetar_archivos(ArchivoEmpaquetable archivos[], int cantidad) {
    if (cantidad == 0) {
        printf("No hay archivos para empaquetar.\n");
        return;
    }

    // Crear ruta de salida con fecha y hora
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char rutaSalida[500];
    strftime(rutaSalida, sizeof(rutaSalida), "/var/log/PROYECTO SO 1/logs%Y-%m-%d-%H%M%S.pak", tm_info);

    // Crear carpeta si no existe
    mkdir("/var/log/PROYECTO SO 1", 0777);
    

    FILE *pak = fopen(rutaSalida, "wb");
    if (!pak) {
        perror("fopen");
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        ArchivoEmpaquetable *arch = &archivos[i];

        // Cabecera: nombre truncado (32 bytes) + tamaño (uint64_t)
        char cabeceraNombre[32] = {0};
        strncpy(cabeceraNombre, arch->nombre_truncado, 31);
        fwrite(cabeceraNombre, sizeof(char), 32, pak);

        uint64_t tam = arch->tamano_bytes;
        fwrite(&tam, sizeof(uint64_t), 1, pak);

        // Escribir contenido del archivo
        printf("Intentando abrir: %s\n", arch->ruta_completa);
        FILE *entrada = fopen(arch->ruta_completa, "rb");
        if (!entrada) {
            perror("fopen archivo");
            continue;
        }

        char buffer[4096];
        size_t leidos;
        while ((leidos = fread(buffer, 1, sizeof(buffer), entrada)) > 0) {
            fwrite(buffer, 1, leidos, pak);
        }

        fclose(entrada);
    }

    // Escribir cabecera final: "FIN" + tamaño 0
    char fin[32] = "FIN";
    fwrite(fin, sizeof(char), 32, pak);
    uint64_t cero = 0;
    fwrite(&cero, sizeof(uint64_t), 1, pak);


    fclose(pak);
    comprimir(rutaSalida);
}
