#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

void copyFiles(int argsLength, char *args[]);

int main(int argc, char *argv[]) {
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