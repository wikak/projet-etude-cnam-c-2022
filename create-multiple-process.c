#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char message[] = "Hello, world!";
    int num_processes = 5;
    int i;

    // Créer un tube anonyme
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Créer plusieurs processus fils
    for (i = 0; i < num_processes; i++) {
        int pid = fork();

        // Code exécuté par le processus père
        if (pid > 0) {
            close(fd[0]); // ferme la fin de lecture du tube
            write(fd[1], message, sizeof(message)); // écrit dans la fin d'écriture du tube
            close(fd[1]); // ferme la fin d'écriture du tube
        }

        // Code exécuté par les processus fils
        else if (pid == 0) {
            char buf[sizeof(message)];
            close(fd[1]); // ferme la fin d'écriture du tube
            read(fd[0], buf, sizeof(buf)); // lit depuis la fin de lecture du tube
            printf("Process %d received message: %s\n", i, buf);
            close(fd[0]); // ferme la fin de lecture du tube
            return 0;
        }

        // Code exécuté en cas d'erreur lors de l'appel à la fonction fork()
        else {
            perror("fork");
            return 1;
        }
    }

    // Attendre la fin des processus fils
    for (i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    return 0;
}