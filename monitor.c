#include "monitor.h"
#include "empaquetador.h"
volatile sig_atomic_t detener = 0;
ArchivoEmpaquetable archivosEmpaquetables[MAX_FILES];
int cantidadEmpaquetables = 0;
void manejar_salida(int signo) {
    detener = 1;
}

// Verifica si el archivo es aceptable: no es directorio y es regular
int archivoAceptado(const char *ruta) {
    struct stat ruta_stat;
    if (stat(ruta, &ruta_stat) != 0) return 0;

    if (S_ISDIR(ruta_stat.st_mode)) {
        // Es un subdirectorio: descartamos
        return 0;
    }

    return S_ISREG(ruta_stat.st_mode);
}

// Ignora archivos terminados en .gz
int ignoraGZ(const char *nombreArchivo) {
    size_t len = strlen(nombreArchivo);
    return len > 3 && strcmp(nombreArchivo + len - 3, ".gz") == 0;
}

// Calcula el hash md5 usando fork + exec + pipe
void md5sum(const char *rutaArchivo, char *md5_salida) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    } else if (pid == 0) {
        close(pipefd[0]); // Hijo: cerrar lectura
        dup2(pipefd[1], STDOUT_FILENO); // Redirigir stdout
        execlp("md5sum", "md5sum", rutaArchivo, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        close(pipefd[1]); // Padre: cerrar escritura
        waitpid(pid, NULL, 0);
        read(pipefd[0], md5_salida, 256);
        close(pipefd[0]);
        md5_salida[strcspn(md5_salida, " ")] = '\0'; // solo el hash
    }
}

void agregarArchivoEmpaquetar(const char *ruta, ArchivoEmpaquetable *lista, int *cantidad) {
    if (*cantidad >= MAX_FILES) return;

    strncpy(lista[*cantidad].ruta_completa, ruta, MAX_PATH_LEN - 1);

    const char *nombre_base = strrchr(ruta, '/');
    if (!nombre_base) nombre_base = ruta;
    else nombre_base++;

    strncpy(lista[*cantidad].nombre_truncado, nombre_base, 31);
    lista[*cantidad].nombre_truncado[31] = '\0';

    struct stat sb;
    if (stat(ruta, &sb) == 0) {
        lista[*cantidad].tamano_bytes = sb.st_size;
    } else {
        lista[*cantidad].tamano_bytes = 0;
    }

    (*cantidad)++;}

void revisarDirectorio(FileHash *hashes_prev, int *num_prev) {
    DIR *dir = opendir(DIRECTORY);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    FileHash hashes_act[MAX_FILES];
    int num_act = 0;
    


    while ((entry = readdir(dir)) != NULL) {
        char rutaArchivo[500];
        snprintf(rutaArchivo, sizeof(rutaArchivo), "%s/%s", DIRECTORY, entry->d_name);

        if (!archivoAceptado(rutaArchivo)) continue;
        if (ignoraGZ(entry->d_name)) continue;

        char md5[200] = {0};
        md5sum(rutaArchivo, md5);

        strcpy(hashes_act[num_act].nombreArchivo, entry->d_name);
        strcpy(hashes_act[num_act].md5, md5);
        strcpy(hashes_act[num_act].rutaCompleta, rutaArchivo);

        num_act++;
    }

    closedir(dir);

    // Comparación con revisión anterior
    for (int i = 0; i < num_act; i++) {
        int encontrar = 0;
        for (int j = 0; j < *num_prev; j++) {
            if (strcmp(hashes_act[i].nombreArchivo, hashes_prev[j].nombreArchivo) == 0) {
                encontrar = 1;
                if (strcmp(hashes_act[i].md5, hashes_prev[j].md5) != 0) {
                    printf("Archivo modificado: %s\n", hashes_act[i].nombreArchivo);
                 agregarArchivoEmpaquetar(hashes_act[i].rutaCompleta, archivosEmpaquetables, &cantidadEmpaquetables);

                }
                break;
            }
        }
        if (!encontrar) {
            printf("Nuevo archivo detectado: %s\n", hashes_act[i].nombreArchivo);
            agregarArchivoEmpaquetar(hashes_act[i].rutaCompleta, archivosEmpaquetables, &cantidadEmpaquetables);
        }
    }

    // Actualizar lista anterior
    *num_prev = num_act;
    memcpy(hashes_prev, hashes_act, sizeof(FileHash) * num_act);
}
