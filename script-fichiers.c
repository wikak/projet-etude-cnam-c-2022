/**
 * https://inf104.wp.imt.fr/tp9-processus/
 * http://30minparjour.la-bnbox.fr/blog/2010/05/15/creer-plusieurs-processus-avec-fork/#:~:text=Cr%C3%A9er%20un%20seul%20processus%20est,et%20dans%20lequel%20pid%3D0%20.
 * https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16421-manipulez-des-fichiers-a-laide-de-fonctions
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FICHIER = 2

// Script de générations de fichiers

// TODO : Il faudra arriver à générer 10.000

int script_de_generation_des_fichiers()
{
      printf("script_de_generation_des_fichiers\n");

      FILE *fichier = NULL;
       int i = 0;
       while (i < 2)
       {
            // fichier = fopen("dossiers/F0001.txt", "a");

            char buffer[32]; // The filename buffer.
            // Put "file" then k then ".txt" in to filename. => f0010 | f00010
            snprintf(buffer, sizeof(char) * 32, "dossiers/f000%i.txt", i);

             fichier = fopen(buffer, "wb");

             if (fichier != NULL)
             {
                  // fputs("Salut les développeurs\nBienvenue sur OpenClassrooms !", fichier);
                 //  fclose(fichier);
             }
             i++;
       }
      return 0;
      //
}
