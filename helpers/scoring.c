#include <stdio.h>
#include <string.h>
#include "../headers/scoring.h"

int score_team_A = 0;
int score_team_B = 0;

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
