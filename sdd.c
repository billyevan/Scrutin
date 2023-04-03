/**
 *@file sdd.c
 *@author Evandion Brilliant KURNIADI
 */
 
#include "global.h"

int ** allocMatrix(int row, int col){
  int ** matrix = malloc(row * sizeof(int *));
  if(matrix == NULL){
    printf("Problème d'allocation.\n");
    exit(1);
  }
  for (i=0;i<row;i++){
    matrix[i] = malloc(col * sizeof(int));
    if(matrix[i] == NULL){
      printf("Problème d'allocation.\n");
      exit(1);
    }
  }
  return matrix;
}

int ** matduel_ballot(int ** mat_ballot, int row, int nbCandidate){
    int ** resultat = allocMatrix(nbCandidate, nbCandidate); //matrice pour stocker les résultats de chaque candidat

  for(i = 0; i<nbCandidate; i++){
    for(int j = 0; j<nbCandidate; j++){
      resultat[i][j] = 0;
    }
  }

  for(int j=0; j<nbCandidate; j++){
    int tabcol[row-1];
    for(i = 0; i < row-1; i++){
      tabcol[i] = mat_ballot[i][j];
    }
    for(int b = 0; b < nbCandidate; b++){
      for(int a = 0; a < row-1; a++){
        if(tabcol[a]<=mat_ballot[a][b] && j != b){
          resultat[j][b] += 1;
        }
      }
    }
  }
/*    
  for(i = 0; i<nbCandidate; i++){
    for(int j = 0; j<nbCandidate; j++){
      printf("%d ",resultat[i][j]);
    }
    printf("\n");
  }*/
  return resultat;
}