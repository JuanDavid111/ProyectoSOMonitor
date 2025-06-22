#include "monitor.h"

volatile sig_atomic_t detener = 0;

void manejar_salida(int signo) {
    detener = 1;
}

int is_regular_file(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) return 0;
    return S_ISREG(path_stat.st_mode);
}

int ends_with_gz(const char *filename) {
    size_t len = strlen(filename);
    return len > 3 && strcmp(filename + len - 3, ".gz") == 0;
}

void compute_md5(const char *filepath, char *md5_output) {
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
        execlp("md5sum", "md5sum", filepath, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        close(pipefd[1]); // Padre: cerrar escritura
        waitpid(pid, NULL, 0);
        read(pipefd[0], md5_output, 256);
        close(pipefd[0]);
        md5_output[strcspn(md5_output, " ")] = '\0';
    }
}

void revisar_directorio(FileHash *hashes_prev, int *num_prev) {
    DIR *dir = opendir(DIRECTORY);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    FileHash hashes_now[MAX_FILES];
    int num_now = 0;

    while ((entry = readdir(dir)) != NULL) {
        char path[512];
        snprintf(path, sizeof(path), "%s/%s", DIRECTORY, entry->d_name);

        if (!is_regular_file(path)) continue;
        if (ends_with_gz(entry->d_name)) continue;

        char md5[256] = {0};
        compute_md5(path, md5);

        strcpy(hashes_now[num_now].filename, entry->d_name);
        strcpy(hashes_now[num_now].md5, md5);
        num_now++;
    }

    closedir(dir);

    for (int i = 0; i < num_now; i++) {
        int found = 0;
        for (int j = 0; j < *num_prev; j++) {
            if (strcmp(hashes_now[i].filename, hashes_prev[j].filename) == 0) {
                found = 1;
                if (strcmp(hashes_now[i].md5, hashes_prev[j].md5) != 0) {
                    printf("Archivo modificado: %s\n", hashes_now[i].filename);
                }
                break;
            }
        }
        if (!found) {
            printf("Nuevo archivo detectado: %s\n", hashes_now[i].filename);
        }
    }

    *num_prev = num_now;
    memcpy(hashes_prev, hashes_now, sizeof(FileHash) * num_now);
}

int main() {
    signal(SIGINT, manejar_salida);

    FileHash previous_hashes[MAX_FILES];
    int num_prev = 0;

    while (!detener) {
        printf("\nRevisando el directorio %s...\n", DIRECTORY);
        revisar_directorio(previous_hashes, &num_prev);
        sleep(INTERVAL);
    }

    printf("\nLog_monitor terminado de forma ordenada.\n");
    return 0;
}
