#include <stdio.h>
#include <stdlib.h>
#include "comprimir_utilidades.h" // Incluye el archivo de cabecera de la función comprimir

int main() {
    const char *pak_file = "mi_juego.pak";

    // ARCHIVO PAK DE PRUEBA
    FILE *fp = fopen(pak_file, "w");

    fprintf(fp, "Contenido de mi archivo .pak para el juego.\n");
    fprintf(fp, "Este es un archivo de prueba que se va a comprimir.\n");
    fprintf(fp, "Más datos para hacer el archivo un poco más grande y ver la compresión.\n");
    fclose(fp);
    // FIN ARCHIVO PAK DE PRUEBA

    comprimir(pak_file);

    printf("\n--- Probando con un archivo inexistente ---\n");
    comprimir("archivo_inexistente.pak");

    return 0;
}