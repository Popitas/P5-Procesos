#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdbool.h>
#include <getopt.h>

bool rMode = false;
bool qMode = false;

void copyFiles(int argsLength, char *args[]);

int main(int argc, char *argv[]) {
    if (rMode)
    copyFiles(argc, argv);
    return 0;
}

void copyFiles(int argsLength, char *args[]) {
    for (int i = 1; i < argsLength - 1; i++) {
        pid_t child_pid = fork();

        if (child_pid != 0) {
            int status;
            wait(&status);
        } else {
            char *cpArgs[] = {"cp", args[i], args[argsLength - 1]};
            execvp("cp", cpArgs);

            perror("No se pudo copiar el archivo");
            printf("\t'%s' falló con errno %d\n", args[i], errno);
            exit(0);
        }
    }
}

int enabledModes(int argc, char *argv[]){
    extern char *optarg;
    extern int optind;
    int c = 0, counter = 0;

    while ((c = getopt(argc, argv, "qr")) != -1){
        switch (c) {
            case 'q':
                counter++;
                qMode = true;
                printf("****(!) Mensajes de error de hilos inhabilitado.\n");
                break;
            case 'r':
                counter++;
                rMode = true;
                printf("****(!) Habilitado el reintento si hay fallos.\n");
                break;
            default:
                break;
        }
    }

    return counter;
}