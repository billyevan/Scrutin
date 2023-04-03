/**
 *@file condorcet.c
 *@author NOM PRENOM
 */
#include "global.h"

void minimax_duel(char * filename,liste liste, int nbCandidate, int row){
  int max = liste.Tabliste[0].poids, imax = liste.Tabliste[0].orig;
  for(i = 1; i < nbCandidate; i++){
    if(liste.Tabliste[i].poids > max){
      max = liste.Tabliste[i].poids;
      imax = liste.Tabliste[i].orig;
    }
  }
  float somme = 0.0;

  for(i = 0; i < nbCandidate; i++){
    somme += liste.Tabliste[i].poids;
  }

  float score = max*100/somme;

  char * gagnant = vainqueurDuel(filename, nbCandidate, &imax);

  gagnant[strcspn(gagnant, "\n")] = 0;
 
  printf("Mode de scrutin : Condorcet minimax, %d candidats, n/a votants, vainqueur = %s, score = %f%%\n", row-1, gagnant, score);
}

void minimax_ballot(char * filename,liste liste, int nbCandidate, int row){
  int max = liste.Tabliste[0].poids, imax = liste.Tabliste[0].orig;
  for(i = 1; i < nbCandidate; i++){
    if(liste.Tabliste[i].poids > max){
      max = liste.Tabliste[i].poids;
      imax = liste.Tabliste[i].orig;
    }
  }
  float somme = 0.0;

  for(i = 0; i < nbCandidate; i++){
    somme += liste.Tabliste[i].poids;
  }

  float score = max*100/somme;

  char * gagnant = vainqueur(filename, nbCandidate, &imax);
 
  printf("Mode de scrutin : Condorcet minimax, %d candidats, %d votants, vainqueur = %s, score = %f%%\n",nbCandidate, row-1, gagnant, score);
}

void creerArcMinimax(Elementliste * e,liste * liste, int ** mat_duel, int nbCandidate){

  int candidat_courant, min, j_min;
  for(i = 0; i < nbCandidate; i++){
    if(i == 0){
      min = mat_duel[i][1];
      j_min = 1;
    }
    else{
      min = mat_duel[i][0];
      j_min = 0;
    }
    for(j = 0; j < nbCandidate; j++){
      if( mat_duel[i][j] < min && i != j){
        min = mat_duel[i][j];
        j_min = j;
      }
    }
    e->orig = i;
    e->dest = j_min;
    e->poids = min;
    addTailList(liste, *e);
    //printf("i : %d j : %d min : %d\n", i,j_min,min);
  }
}

void creerArcSchulze(Elementliste * e,liste * liste, int ** mat_duel, int nbCandidate){

  int candidat_courant, max, j_orig,j_dest;

  for(i = 0; i < nbCandidate; i++){
    for(j = 0; j < nbCandidate; j++){
      if(i>j){
        if(mat_duel[i][j] > mat_duel[j][i]){
          max = mat_duel[i][j];
          j_orig = i;
          j_dest = j;
        }
        else if(mat_duel[i][j] < mat_duel[j][i]){
          max = mat_duel[j][i];
          j_orig = j;
          j_dest = i;
        }
        e->orig = j_orig;
        e->dest = j_dest;
        e->poids = max;
        addTailList(liste, *e);
      }
    }
  }
}

void schulze_duel(char * filename,int **mat_duel, int nbCandidate, int row){

//  int ** matrice_result = allocMatrix(nbCandidate, nbCandidate);
//  int orig, dest;

  int matrice_result[nbCandidate][nbCandidate];
  int orig, dest;

  for(i = 0;i < nbCandidate; i++){
    for(j = 0;j < nbCandidate; j++){
      matrice_result[i][j] = 0;
    }
  }  
   
  for(i = 0; i < nbCandidate; i++){
    for(j = 0; j < nbCandidate; j++){
      if(i != j){
        if(mat_duel[i][j]>mat_duel[j][i]){
          matrice_result[i][j] = mat_duel[i][j];
        }
        else{
          matrice_result[i][j] = 0;
        }
      }
    }
  }

  for(i = 0; i < nbCandidate; i++){
    for(j = 0; j < nbCandidate; j++){
      if(i != j){
        for(int k = 0; k < nbCandidate; k++){
          if(i != k && j != k){
            matrice_result[j][k] = MAXI(matrice_result[j][k], MIN(matrice_result[j][i],matrice_result[i][k]));
          }
        }
      }
    }
  }


  int sum_max = 0, somme = 0;
  int somme_de_tout = 0;
  int i_vainqueur;

  for(i = 0; i < nbCandidate; i++){
    for(j = 0; j < nbCandidate; j++){
      somme += matrice_result[i][j];
      somme_de_tout += matrice_result[i][j];
    }
    if(somme > sum_max){
      sum_max = somme;
      i_vainqueur = i;
    }
    somme = 0;
  }
  
  //printf("\n%d\n", somme_de_tout);
  

  int score = sum_max*100/somme_de_tout;

  
  char * gagnant = vainqueurDuel(filename, nbCandidate, &i_vainqueur);

  gagnant[strcspn(gagnant, "\n")] = 0;

  printf("Mode de scrutin : Condorcet schulze, %d candidats, n/a votants, vainqueur = %s, score = %d%%\n",nbCandidate, gagnant, score);
}

void schulze_ballot(char * filename,int **mat_duel, int nbCandidate, int row){

//  int ** matrice_result = allocMatrix(nbCandidate, nbCandidate);
//  int orig, dest;

  int matrice_result[nbCandidate][nbCandidate];
  int orig, dest;

  for(i = 0;i < nbCandidate; i++){
    for(j = 0;j < nbCandidate; j++){
      matrice_result[i][j] = 0;
    }
  }  
   
  for(i = 0; i < nbCandidate; i++){
    for(j = 0; j < nbCandidate; j++){
      if(i != j){
        if(mat_duel[i][j]>mat_duel[j][i]){
          matrice_result[i][j] = mat_duel[i][j];
        }
        else{
          matrice_result[i][j] = 0;
        }
      }
    }
  }

  for(i = 0; i < nbCandidate; i++){
    for(j = 0; j < nbCandidate; j++){
      if(i != j){
        for(int k = 0; k < nbCandidate; k++){
          if(i != k && j != k){
            matrice_result[j][k] = MAXI(matrice_result[j][k], MIN(matrice_result[j][i],matrice_result[i][k]));
          }
        }
      }
    }
  }


  int sum_max = 0, somme = 0;
  int somme_de_tout = 0;
  int i_vainqueur;

  for(i = 0; i < nbCandidate; i++){
    for(j = 0; j < nbCandidate; j++){
      somme += matrice_result[i][j];
      somme_de_tout += matrice_result[i][j];
    }
    if(somme > sum_max){
      sum_max = somme;
      i_vainqueur = i;
    }
    somme = 0;
  }
  
  //printf("\n%d\n", somme_de_tout);
  

  int score = sum_max*100/somme_de_tout;

  
  char * gagnant = vainqueur(filename, nbCandidate, &i_vainqueur);

  printf("Mode de scrutin : Condorcet schulze, %d candidats, %d votants, vainqueur = %s, score = %d%%\n",nbCandidate,row-1, gagnant, score);
}

// Fonction qui recupere le nom des candidats (csv matrice duel) en les mettants dans un tableau
char * vainqueurDuel(char * filename, int nbCandidate, int * imax){
  i = 0; j = 0;
  char line[1024];
  char * candidateName[nbCandidate];
  
  FILE * file = fopen(filename, "r");
    
  if (file == NULL){
    printf("Erreur, impossible d'ouvrir le fichier.");
    exit(EXIT_FAILURE);
  }
  
  char * firstline = fgets(line, 1024, file);
  char * name = strtok(firstline, ",");

  while (name != NULL){
    candidateName[i] = name;
    name = strtok(NULL, ",");
    i++;
  }
  //for(i = 0; i < nbCandidate; i++)
    //printf("%s\n", candidateName[i]);
  printf(" ");
  return candidateName[*imax];
}






