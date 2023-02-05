/**
 * https://inf104.wp.imt.fr/tp9-processus/
 * http://30minparjour.la-bnbox.fr/blog/2010/05/15/creer-plusieurs-processus-avec-fork/#:~:text=Cr%C3%A9er%20un%20seul%20processus%20est,et%20dans%20lequel%20pid%3D0%20.
 * https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16421-manipulez-des-fichiers-a-laide-de-fonctions
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include "helpers/scoring.c"
#include "helpers/itoa.c"
// #include "headers/variables.h"

#define FICHIER = 2
#define TAILLE_MAX 1000

void handle_sigterm(int signal)

{
      printf("Processus terminé avec le signal %d\n", signal);
      _exit(0);
}

void handle_mysigterm()

{
      printf("Processus terminé avec le signal\n");
      _exit(0);
}

void gestionnaire_alarme(int signum)
{
      printf("L'alarme a été déclenchée\n");
}

void gestionnaire_quitter(int signum)
{
      printf("Le processus va être terminé avec le signal SIGQUIT\n");
      exit(0);
}

int main(int argc, char *argv[])
{
      // signal(SIGTERM, handle_sigterm);
      signal(SIGALRM, gestionnaire_alarme);
      alarm(10);
      pause();

      // On initilise les informations du pipe
      // int fd[2];
      char buffer[100];

      char binary_string[33];

      // On initilise les compteurs
      int i, j = 0;

      // Equipe A
      // Processus principal Equipe A
      char QGA[33], QGA1[33];

      // Processus attaquant Equipe A
      pid_t ProcessusQGA, ProcessusA1;
      pid_t PidProcessusA1 = 128;

      // Equipe B
      // Equipe A
      // Processus principal Equipe A
      char QGB[33], QGB1[33], QGB2[33];

      // Processus attaquant Equipe B
      pid_t ProcessusQGB, ProcessusB1, ProcessusB2;
      pid_t PidProcessusB1 = 170;

      // TODO : Les variables des équipes doivent être écrite en binaire

      char NumEquipA[33];
      itoa(20, NumEquipA, 2);

      char NumEquipB[33];
      itoa(21, NumEquipB, 2);

      char resultat[500];

      //   printf("Le numéro de l'équipe A est %d\n", NumEquipA);

      // script_de_generation_des_fichiers();

      int fd[2];

      int ret = pipe(fd);

      char message_to_send[] = "";
      const char delimiter[] = ",";

      FILE *fichier = NULL;

      char *token;

      char buf[100];

      int size;

      if (ret == -1)
      {
            perror("Pipe creation failed");
            exit(EXIT_FAILURE);
      }

      // ÉQUIPE A
      // Créer le processus parent A
      ProcessusQGA = fork();

      // On vérifie si le processus A a bien été crée
      if (ProcessusQGA == 0)
      {
            // Premier processus fils
            ProcessusA1 = fork();
            // char received_message[100], send_message[100];

            if (ProcessusA1 == 0)
            {

                  itoa(getpid(), QGA1, 2);
                  //  printf("Mon 1er fils pid du processus A %s .\n", QGA1);
                  char buf[sizeof(message_to_send)];
                  close(fd[1]);                  // ferme la fin d'écriture du tube
                  read(fd[0], buf, sizeof(buf)); // lit depuis la fin de lecture du tube
                                                     // printf("received message 1er fils du processus A: %s\n", buf);
                  fichier = fopen("dossiers/f0000.txt", "a+");
                  if (fichier != NULL)
                  {

                        // On vérifie si le fichier n'est pas vide
                        fseek(fichier, 0, SEEK_END);
                        size = ftell(fichier);

                        printf("La taille du fichier est de %d avant que A écrive \n", size);
                        if (size == 0)
                        {
                              printf("Le fichier est vide A est prêt!\n");
                              // Num Équipe et PID de l'attaquant
                              strcpy(resultat, "Num Equipe A : ");
                              strcat(resultat, NumEquipA);
                              strcat(resultat, " - PID attaquant : ");
                              strcat(resultat, QGA1);
                              strcat(resultat, "\n");
                              //  printf("Résultat : %s\n", resultat);
                              fprintf(fichier, "%s", resultat);
                              scoring("teamA");
                              //  handle_mysigterm();
                        }
                        else
                        {

                              // read_info_in_file(fichier);
                              printf("File is not empty Team B already write!\n");
                              printf("PidProcessusB1 dans Processus A : %d\n", PidProcessusB1);
                              strcpy(resultat, "Mort du Processus B1. Num Equipe A ");
                              strcat(resultat, NumEquipA);
                              strcat(resultat, " - PID attaquant : ");
                              strcat(resultat, QGA1);
                              strcat(resultat, "\n");
                              fprintf(fichier, "%s", resultat);
                              scoring("teamA");

                              signal(SIGQUIT, gestionnaire_quitter);
                              printf("Envoi du signal SIGQUIT\n");
                              raise(SIGQUIT);
                              /// fprintf(fichier, "Mort du Processus B1\nTeam A- Processus A1\n");
                              // handle_mysigterm(PidProcessusB1);
                              // kill(PidProcessusB1, SIGTERM);

                              /**int result = kill(PidProcessusB1, SIGKILL);
                              if (result == -1)
                              {
                                    perror("Error killing process");
                              }
                              else
                              {
                                    printf("File is not empty Team B already write!\n");
                                    fprintf(fichier, "Team A- Processus A1\n");
                                    fclose(fichier);
                                    scoring("teamA");
                              }**/
                        }

                        //
                  }

                  // Si le fichier est vide j'écris le message suivant : Team A1 - Attaquant  QGA1

                  close(fd[0]);
                  // return 0;
            }
            // return 0;
            //  signal(SIGTERM, handle_sigterm);
      }
      else
      {
            itoa(getpid(), QGA, 2);
            // printf("Mon pid du processus principal A %s .\n", QGA);

            close(fd[0]); // ferme la fin de lecture du tube
            write(fd[1], message_to_send, strlen(message_to_send) + 1);
            close(fd[1]); /** */

            // Processus père
            /**  close(fd[0]);
               strcpy(buffer, "Bonjour, je suis le processus père !\n");
               write(fd[1], buffer, strlen(buffer) + 1);*/
      }

      // ÉQUIPE B

      // Créer le processus parent A
      ProcessusQGB = fork();

      // On vérifie si le processus A a bien été crée
      if (ProcessusQGB == 0)
      {
            // Premier processus fils
            ProcessusB1 = fork();
            // char received_message[100], send_message[100];

            if (ProcessusB1 > 0)
            {
                  itoa(getpid(), QGB1, 2);
                  //  printf("Mon 1er fils pid du processus B %s .\n", QGB1);
                  char buf[sizeof(message_to_send)];
                  close(fd[1]);                  // ferme la fin d'écriture du tube
                  read(fd[0], buf, sizeof(buf)); // lit depuis la fin de lecture du tube
                  // printf("received message 1er fils du processus B: %s\n", buf);

                  fichier = fopen("dossiers/f0000.txt", "a+");
                  if (fichier != NULL)
                  {

                        // On vérifie si le fichier n'est pas vide

                        fseek(fichier, 0, SEEK_END);
                        size = ftell(fichier);

                        printf("La taille du fichier est de %d avant que B écrive \n", size);
                        //  handle_mysigterm(PidProcessusA1);
                        if (size == 0)
                        {
                              strcpy(resultat, "Num Equipe B : ");
                              strcat(resultat, NumEquipB);
                              strcat(resultat, " - PID attaquant : ");
                              strcat(resultat, QGB1);
                              strcat(resultat, "\n");
                              printf("Le fichier est vide B est prêt!\n");
                              fprintf(fichier, "%s", resultat);
                              scoring("teamB");
                              //  handle_mysigterm();
                        }
                        else
                        {

                              printf("File is not empty Team A already write!\n");
                              printf("PidProcessusAttaquanA1 dans Processus B : %d\n", PidProcessusA1);
                              strcpy(resultat, "Mort du Processus A1. Num Equipe B ");
                              strcat(resultat, NumEquipB);
                              strcat(resultat, " - PID attaquant : ");
                              strcat(resultat, QGB1);
                              strcat(resultat, "\n");
                              fprintf(fichier, "%s", resultat);
                              //  fprintf(fichier, "Mort du Processus A1\nTeam B- Processus B1\n");
                              scoring("teamB");
                              signal(SIGQUIT, gestionnaire_quitter);
                              printf("Envoi du signal SIGQUIT\n");
                              raise(SIGQUIT);
                        }

                        //
                  }

                  close(fd[0]);
                  // return 0;
            }
            return 0;
            //  signal(SIGTERM, handle_sigterm);
      }
      else
      {
            itoa(getpid(), QGB, 2);
            //  printf("Mon pid  du processus principal B %s .\n", QGA);

            close(fd[0]); // ferme la fin de lecture du tube
            write(fd[1], message_to_send, strlen(message_to_send) + 1);
            close(fd[1]); /** */

            // Processus père
            /**  close(fd[0]);
               strcpy(buffer, "Bonjour, je suis le processus père !\n");
               write(fd[1], buffer, strlen(buffer) + 1);*/
      }
     // printf("Scrore finale : \n Équipe A : %s\n Équipe B : %s \n",score_team_A, score_team_B );
      return 0;
      // Ici c'est le processus du père
}
