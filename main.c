
#include "monitor.h"
#include "empaquetador.h"

int main() {
    signal(SIGINT, manejar_salida);

    FileHash hashes_anteriores[MAX_FILES];
    int num_prev = 0;

    while (!detener) {
        printf("\nRevisando el directorio %s...\n", DIRECTORY);
        revisarDirectorio(hashes_anteriores, &num_prev);
        empaquetar_archivos(archivosEmpaquetables, cantidadEmpaquetables); // <- Aquí se empaquetan
        cantidadEmpaquetables = 0;  // Limpiar para siguiente ronda
        sleep(INTERVAL);
    }

    printf("\nLog_monitor terminado de forma ordenada.\n");
    return 0;
}