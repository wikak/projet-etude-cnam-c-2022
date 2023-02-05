#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

  // On initilise les informations du pipe
      extern int pipefd[2];
     extern   char buffer[100];

      extern  char binary_string[33];

      // Equipe A
      // Processus principal Equipe A
      extern  char QGA[33], QGA1[33], QGA2[33];

      // Processus attaquant Equipe A
      extern  pid_t ProcessusA, ProcessusAttaquantA1;
      extern  pid_t PidProcessusAttaquantA1;

      // Equipe B
      // Equipe A
      // Processus principal Equipe A
      extern  char QGB[33], QGB1[33], QGB2[33];

      // Processus attaquant Equipe B
      extern  pid_t ProcessusB, ProcessusAttaquantB1;
      extern  pid_t PidProcessusAttaquantB1;


      extern  char NumEquipA[33];
  

      extern  char NumEquipB[33];
  

      extern  char resultat[500];


      extern  int fd[2];

      extern  int ret;

      extern  char message_to_send[];
      extern  const char delimiter[];

       extern FILE *fichier;

       extern char *token;

       extern char buf[100];

       extern int size;
