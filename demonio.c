#include "demonio.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // Para fork, setsid, chdir, close, dup, sysconf
#include <sys/types.h>  // Para pid_t
#include <sys/stat.h>   // Para umask
#include <fcntl.h>      // Para open (con O_RDWR)
#include <syslog.h>     // Para syslog
#include <string.h>     // Para strerror
#include <errno.h>      // Para errno
#include <signal.h>



void demonizar() {
    int fd;
    pid_t pid;

    // Crear un nuevo proceso hijo
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        // Terminar el proceso padre
        exit(EXIT_SUCCESS);
    }

    // Crear una nueva sesión
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    // Ignorar señales SIGHUP y SIGCHLD
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);


    // Segundo fork para evitar adquirir terminal de control
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Establecer umask a 0
    umask(0);


    // Cambiar el directorio de trabajo a la raíz
    if (chdir("/") < 0) {
        syslog(LOG_ERR, "Error al cambiar el directorio de trabajo: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Cerrar los descriptores de archivo estándar
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Redirigir stdin, stdout y stderr a /dev/null
    fd = open("/dev/null", O_RDWR);
    if (fd != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
    if (fd > STDERR_FILENO) {
        close(fd);
    }
    } else {
        syslog(LOG_ERR, "No se pudo abrir /dev/null: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
}