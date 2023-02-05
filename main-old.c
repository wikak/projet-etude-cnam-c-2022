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

#define FICHIER = 2
#define TAILLE_MAX 1000

// Script de générations de fichiers

// TODO : Il faudra arriver à générer 10.000

/**int write_in_file_when_is_empty(team, ProcessusAttaquant, fichier)
{
      char str[80];
      strcpy(str, "team ");
      strcat(str, team);
      strcat(str, "ProcessusAttaquant ");
      strcat(str, ProcessusAttaquant);
      strcat(str, "\n");
      puts(str);
      fputs(str, fichier);
      fclose(fichier);
}*/

/**int convertir_en_binaire_pid(pid)
{
      int tab[10], i;
       printf("Le pid de l'attaquant: %d\n", pid);

      for (i = 0; pid > 0; i++)
      {
            tab[i] = pid % 2;
            pid = pid / 2;
      }
       for(i=i-1; i >= 0; i--) {
            printf("\nLe nombre binaire est = %d", tab[i]);
       }
      return 0;

}*/
int score_team_A = 0;
int score_team_B = 0;
void write_info_in_file(char *message, FILE *fichier)
{
      // fputs(message, fichier);
      // fclose(fichier);
      char chaine[TAILLE_MAX] = "";

      //  char *team = "Team A";
      // char *ProcessusAttaquant = "ProcessusAttaquant A1";

      fprintf(fichier, "%s", message);

      // Si le fichier est vide

      // Si le fichier n’est pas vide
      // Sinon si l’attaquant n’est pas de la même équipe que celui qui vient de précédemment écrire
}

void read_file(char *message, FILE *fichier, char *searchTerm)
{

      char chaine[TAILLE_MAX] = "";
      char line[TAILLE_MAX];
      fseek(fichier, -TAILLE_MAX, SEEK_END);
      printf("read_info_in_file\n");

      while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
      {
            printf("Search term found: %s", line);
            if (strstr(line, searchTerm))
            {
                  printf("Search term found: %s", line);
                  break;
            }
            else
            {
                  printf("Le term n'ont trouvé");
                  write_info_in_file(message, fichier);
            }
      }
}

void scoring(char *team)
{
      if (strcmp(team, "teamA") == 0)
      {
            score_team_A += 1;
      }
      else if (strcmp(team, "teamB") == 0)
      {
            score_team_B += 1;
      }

      printf("score de la team A : %d\n", score_team_A);
      printf("score de la team B : %d\n", score_team_B);
}

// Script de génération des fichiers
void script_de_generation_des_fichiers()
{
      // printf("script_de_generation_des_fichiers\n");

      // FILE *fichier = NULL;
      int i = 0;

      while (i < 1)
      {
            // fichier = fopen("dossiers/F0001.txt", "a");

            // char buffer[32]; // The filename buffer.
            // Put "file" then k then ".txt" in to filename. => f0010 | f00010
            // snprintf(buffer, sizeof(char) * 32, "dossiers/f000%i.txt", i);

            // fichier = fopen("dossiers/f000%i.txt", "rwb");
            // fichier = fopen("dossiers/f0000.txt", "rwb");

            i++;
      }

      //
}

void handle_sigterm(int sig)

{
      printf("Processus terminé avec le signal %d\n", sig);
      _exit(0);
}

void sig_handler(int signum)
{
      printf("Signal %d received\n", signum);
}

char *itoa(int value, char *result, int base)
{
      // check that the base if valid
      if (base < 2 || base > 36)
      {
            *result = '\0';
            return result;
      }

      char *ptr = result, *ptr1 = result, tmp_char;
      int tmp_value;

      do
      {
            tmp_value = value;
            value /= base;
            *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
      } while (value);

      // Apply negative sign
      if (tmp_value < 0)
            *ptr++ = '-';
      *ptr-- = '\0';
      while (ptr1 < ptr)
      {
            tmp_char = *ptr;
            *ptr-- = *ptr1;
            *ptr1++ = tmp_char;
      }
      return result;
}

void kill_process(int pid)
{
      signal(SIGQUIT, handle_sigterm);
      kill(pid, SIGQUIT);
}

int main(void)
{
      signal(SIGALRM, sig_handler);
      // Définissez un temporisateur pour 20 secondes
      // alarm(20);
      // pause();

      // On initilise les informations du pipe
      int pipefd[2];
      char buffer[100];

      char binary_string[33];

      // On initilise les compteurs
      int i, j = 0;

      // Equipe A
      // Processus principal Equipe A
      char QGA[33], QGA1[33], QGA2[33];

      // Processus attaquant Equipe A
      pid_t ProcessusA, ProcessusAttaquantA1, ProcessusAttaquantA2;
      pid_t PidProcessusAttaquantA1;

      // Equipe B
      // Equipe A
      // Processus principal Equipe A
      char QGB[33], QGB1[33], QGB2[33];

      // Processus attaquant Equipe B
      pid_t ProcessusB, ProcessusAttaquantB1, ProcessusAttaquantB2;
      pid_t PidProcessusAttaquantB1;

      // TODO : Les variables des équipes doivent être écrite en binaire

      char NumEquipA[33];
      itoa(1, NumEquipA, 2);

      char NumEquipB[33];
      itoa(1, NumEquipB, 2);

      //   printf("Le numéro de l'équipe A est %d\n", NumEquipA);

      // script_de_generation_des_fichiers();

      int fd[2];

      int ret = pipe(pipefd);

      char message_to_send[] = "f0000,f0001";
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
      ProcessusA = fork();

      // On vérifie si le processus A a bien été crée
      if (ProcessusA == 0)
      {
            // Premier processus fils
            ProcessusAttaquantA1 = fork();
            // char received_message[100], send_message[100];

            if (ProcessusAttaquantA1 == 0)
            {
                  // Deuxième processus fils
                  ProcessusAttaquantA2 = fork();
                  if (ProcessusAttaquantA2 == 0)
                  {

                        itoa(getpid(), QGA2, 2);
                       // printf("Mon 2ème fils pid du processus A  %s .\n", QGA2);
                        char buf[sizeof(message_to_send)];
                        close(pipefd[1]);                  // ferme la fin d'écriture du tube
                        read(pipefd[0], buf, sizeof(buf)); // lit depuis la fin de lecture du tube
                      //  printf("received message 2ème fils du processus A: %s\n", buf);
                        close(pipefd[0]); // ferme la fin de lecture du tube
                        return 0;
                  }
            }
            else
            {
                  PidProcessusAttaquantA1 = getpid();
                  itoa(getpid(), QGA1, 2);
                //  printf("Mon 1er fils pid du processus A %s .\n", QGA1);
                  char buf[sizeof(message_to_send)];
                  close(pipefd[1]);                  // ferme la fin d'écriture du tube
                  read(pipefd[0], buf, sizeof(buf)); // lit depuis la fin de lecture du tube
                 // printf("received message 1er fils du processus A: %s\n", buf);
                  fichier = fopen("dossiers/f0000.txt", "wr");
                  if (fichier != NULL)
                  {

                        // On vérifie si le fichier n'est pas vide

                        fseek(fichier, 0, SEEK_END);
                        size = ftell(fichier);

                        if (size == 0)
                        {
                              printf("Le fichier est vide!\n");
                              fprintf(fichier, "Team A- ProcessusAttaquant A1\n");
                              scoring("teamA");
                              fclose(fichier);
                        }
                        else
                        {
                              // read_info_in_file(fichier);
                              // printf("File is not empty Team B already write!\n");
                              printf("PidProcessusAttaquantB1 : %d!\n", PidProcessusAttaquantB1);
                              int result = kill(PidProcessusAttaquantB1, SIGKILL);
                              if (result == -1)
                              {
                                    perror("Error killing process");
                              }
                              else
                              {
                                    printf("File is not empty Team A already write!\n");
                                    fprintf(fichier, "Team A- ProcessusAttaquant A1\n");
                                    fclose(fichier);
                                    scoring("teamA");
                              }
                        }

                        //
                  }
                  // Si le fichier est vide j'écris le message suivant : Team A1 - Attaquant  QGA1

                  close(pipefd[0]);
                  return 0;
            }
            return 0;
            //  signal(SIGTERM, handle_sigterm);
      }
      else
      {
            itoa(getpid(), QGA, 2);
            // printf("Mon pid du processus principal A %s .\n", QGA);

            close(pipefd[0]); // ferme la fin de lecture du tube
            write(pipefd[1], message_to_send, strlen(message_to_send) + 1);
            close(pipefd[1]); /** */

            // Processus père
            /**  close(pipefd[0]);
               strcpy(buffer, "Bonjour, je suis le processus père !\n");
               write(pipefd[1], buffer, strlen(buffer) + 1);*/
      }

      // ÉQUIPE B

      // Créer le processus parent A
      ProcessusB = fork();

      // On vérifie si le processus A a bien été crée
      if (ProcessusB == 0)
      {
            // Premier processus fils
            ProcessusAttaquantB1 = fork();
            // char received_message[100], send_message[100];

            if (ProcessusAttaquantB1 == 0)
            {
                  // Deuxième processus fils
                  ProcessusAttaquantB2 = fork();
                  if (ProcessusAttaquantB2 == 0)
                  {
                        itoa(getpid(), QGB2, 2);
                     //   printf("Mon 2ème fils pid du processus B %s .\n", QGB2);
                        char buf[sizeof(message_to_send)];
                        close(pipefd[1]);                  // ferme la fin d'écriture du tube
                        read(pipefd[0], buf, sizeof(buf)); // lit depuis la fin de lecture du tube
                       // printf("received message 2ème fils du processus B: %s\n", buf);
                        close(pipefd[0]); // ferme la fin de lecture du tube
                        return 0;
                  }
            }
            else
            {
                  PidProcessusAttaquantB1 = getpid();
                  itoa(getpid(), QGB1, 2);
                //  printf("Mon 1er fils pid du processus B %s .\n", QGB1);
                  char buf[sizeof(message_to_send)];
                  close(pipefd[1]);                  // ferme la fin d'écriture du tube
                  read(pipefd[0], buf, sizeof(buf)); // lit depuis la fin de lecture du tube
                  // printf("received message 1er fils du processus B: %s\n", buf);

                  fichier = fopen("dossiers/f0000.txt", "wr");
                  if (fichier != NULL)
                  {

                        // On vérifie si le fichier n'est pas vide

                        fseek(fichier, 0, SEEK_END);
                        size = ftell(fichier);

                        if (size == 0)
                        {
                              printf("Le fichier est vide!\n");
                              fprintf(fichier, "Team B- ProcessusAttaquant B1\n");
                              scoring("teamB");
                              fclose(fichier);
                        }
                        else
                        {
                              printf("PidProcessusAttaquantA1 : %d!\n", PidProcessusAttaquantA1);
                              int result = kill(PidProcessusAttaquantA1, SIGKILL);
                              if (result == -1)
                              {
                                    perror("Error killing process");
                              }
                              else
                              {
                                    printf("File is not empty Team A already write!\n");
                                    fprintf(fichier, "Team B- ProcessusAttaquant B1\n");
                                    fclose(fichier);
                                    scoring("teamB");
                              }
                              // read_info_in_file("",fichier,);
                        }

                        //
                  }

                  close(pipefd[0]);
                  return 0;
            }
            return 0;
            //  signal(SIGTERM, handle_sigterm);
      }
      else
      {
            itoa(getpid(), QGB, 2);
          //  printf("Mon pid  du processus principal B %s .\n", QGA);

            close(pipefd[0]); // ferme la fin de lecture du tube
            write(pipefd[1], message_to_send, strlen(message_to_send) + 1);
            close(pipefd[1]); /** */

            // Processus père
            /**  close(pipefd[0]);
               strcpy(buffer, "Bonjour, je suis le processus père !\n");
               write(pipefd[1], buffer, strlen(buffer) + 1);*/
      }
      return 0;
      // Ici c'est le processus du père
}
