#include "demonio.h"     // Para la función demonizar
#include <string.h>     // Para strerror
#include <errno.h>      // Para errno

#include <stdio.h>        // Para fprintf
#include <stdlib.h>       // Para EXIT_FAILURE, EXIT_SUCCESS
#include <unistd.h>       
#include <syslog.h>






int main()
{
    demonizar();
    openlog("prueba", LOG_PID | LOG_CONS, LOG_DAEMON);
    syslog(LOG_INFO, "El demonio se ha iniciado correctamente.");
    while (1) {
        syslog(LOG_INFO, "El demonio está trabajando...");
        sleep(10);  // Espera 10 segundos antes de la siguiente iteración
    }
    syslog(LOG_INFO, "salio");
    // Cerrar syslog al finalizar
    closelog();
    

    
    return 0;
}
