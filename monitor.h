#ifndef MONITOR_H
#define MONITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define DIRECTORY "/var/log"
#define INTERVAL 10 // tiempo entre revisiones (segundos)
#define MAX_FILES 2000
#define BUFFER_SIZE 4096

typedef struct {
    char nombreArchivo[200];
    char rutaCompleta[500];
    char md5[40];
} FileHash;


extern volatile sig_atomic_t detener;

void manejar_salida(int signo);
int archivoAceptado(const char *rutaArchivo);
int ignorarGZ(const char *nombreArchivo);
void md5sum(const char *filepath, char *md5_output);
void revisarDirectorio(FileHash *hashes_prev, int *num_prev, int *contador_intervalos);

#endif // PRUEBA3_H