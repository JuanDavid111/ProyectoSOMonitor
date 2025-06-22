#include "comprimir_utilidades.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int comprimir(const char *filename) {
    pid_t pid;
    int status;
    char archivo_comprimido[256];

    snprintf(archivo_comprimido, sizeof(archivo_comprimido), "%s.gz", filename);
    pid = fork();

    if(pid == 0){

        execlp("gzip", "gzip", filename, NULL);
        exit(EXIT_FAILURE);

    }else{
        if(waitpid(pid, &status, 0) == -1){
            return -1;
        }

        if(WIFEXITED(status)){
            int exit_status = WEXITSTATUS(status);
            if(exit_status == 0){
                return 0;
            }else{
                return -1;
            }
        }else{
            return -1;
        }
    }
}