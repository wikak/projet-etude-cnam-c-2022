/**
 * https://inf104.wp.imt.fr/tp9-processus/
 * http://30minparjour.la-bnbox.fr/blog/2010/05/15/creer-plusieurs-processus-avec-fork/#:~:text=Cr%C3%A9er%20un%20seul%20processus%20est,et%20dans%20lequel%20pid%3D0%20.
 * https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16421-manipulez-des-fichiers-a-laide-de-fonctions
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FICHIER = 2

int script_de_generation_des_fichiers()
{
      int i;
      while (i < 2)
      {
            FILE *fichier = NULL;
            fichier = fopen("./dossiers/F0001.txt", "rt");

             
    if (fichier != NULL)
    {
        fputs("Salut les développeurs\nBienvenue sur OpenClassrooms !", fichier);
        fclose(fichier);
    }

            return 0;
            i++;
      }
}

int main(void)
{

      // On initiliase les compteurs
      int i, j = 0;

      // Equipe A
      // Processus principal Equipe A
      pid_t QGA;

      // Processus attaquant Equipe A
      pid_t ProcessusAttaquantA[5];

      // Numéro de l'Equipe A
      int NumEquipA;

      // Fonction chargé d'initaliser la création des processus
      int ProcessusA;

      // Equipe B
      // Processus principal Equipe B
      pid_t QGB;

      // Processus attaquant Equipe B
      pid_t ProcessusAttaquantB[5];

      // Numéro de l'Equipe B
      int NumEquipB;

      // Fonction chargé d'initaliser la création des processus
      int ProcessusB;

      // TODO : Les variables des équipes doivent être écrite en binaire

      NumEquipA = rand();

      printf("Le numéro de l'équipe A est %d\n", NumEquipA);

      // Créer le processus parent A
      ProcessusA = fork();

      // Ici c'est le processus du père
      if (ProcessusA > 0)
      {
            printf("Mon pid %d .\n", getpid());
            QGA = getpid();
      }

      // On vérifie si le processus A a bien été crée
      if (ProcessusA == 0)
      {
            // Génération des processus attaquants (Processus enfant de A)

            // TODO : Trouver le moyen de générer des pid distincts pour les fils

            printf("Mon pid %d .\n", getppid());
            while (i < 5)
            {
                  short pid = getpid();
                  printf("Je suis le fils n°%d-%d  du Processus A, mon père est %d\n", i, getpid(), getppid());
                  ProcessusAttaquantA[i] = getpid();
                  i++;
            }

            exit(0);
      }

      NumEquipB = rand();
      printf("Le numéro de l'équipe B est %d\n", NumEquipB);

      // Créer le processus parent A
      ProcessusB = fork();

      // Ici c'est le processus du père
      if (ProcessusB > 0)
      {
            printf("Mon pid %d .\n", getpid());
            QGA = getpid();
      }

      // On vérifie si le processus A a bien été crée
      if (ProcessusB == 0)
      {
            // Génération des processus attaquants (Processus enfant de A)

            // TODO : Trouver le moyen de générer des pid distincts pour les fils

            printf("Mon pid %d .\n", getppid());
            while (i < 5)
            {
                  short pid = getpid();
                  printf("Je suis le fils n°%d-%d  du Processus B, mon père est %d\n", i, getpid(), getppid());
                  ProcessusAttaquantB[i] = getpid();
                  i++;
            }

            exit(0);
      }

      script_de_generation_des_fichiers();
}
