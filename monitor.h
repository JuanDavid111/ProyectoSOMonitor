#ifndef PRUEBA3_H
#define PRUEBA3_H

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
#define MAX_FILES 1024
#define BUFFER_SIZE 4096

typedef struct {
    char filename[256];
    char md5[256];
} FileHash;

extern volatile sig_atomic_t detener;

void manejar_salida(int signo);
int is_regular_file(const char *path);
int ends_with_gz(const char *filename);
void compute_md5(const char *filepath, char *md5_output);
void revisar_directorio(FileHash *hashes_prev, int *num_prev);

#endif // PRUEBA3_H
