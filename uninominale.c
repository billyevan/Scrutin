/**
 *@file uninominal.c
 *@author Evandion Brilliant KURNIADI
 */
#include "global.h"

void uninominal1(char * filename, int ** mat_ballot, int row, int nbCandidate){

  int * tab = malloc((nbCandidate) * sizeof(int));
  
  for(i = 0; i < nbCandidate; i++){
    tab[i] = 0;
  }
  for(i = 0; i < row-1; i++){ 
    for(int j = 0;j < nbCandidate; j++){
      int val_courante = mat_ballot[i][j];
      for(int k = 0; k < nbCandidate; k++){
        if(val_courante < mat_ballot[i][k] && j != k){  
        tab[j] = tab[j] + 1;
       }
      }
    }
  }

  int vote_max, imax;
  vote_max = tab[0];
  imax = 0;
  
  float sum = 0.0;
  for (i =0; i < nbCandidate; i++){
    sum += tab[i];
  }

  for (i = 0; i < nbCandidate; i++){
    if (tab[i] > vote_max){
      vote_max = tab[i];
      imax = i;
    }
  }

  float score = tab[imax] * 100 / sum;
  
  char * gagnant = vainqueur(filename, nbCandidate, &imax);

  printf("Mode de scrutin : uninominal à un tours, %d candidats, %d votants, vainqueur = %s, score = %f%%\n",nbCandidate, row-1, gagnant, score);
  
}

void uninominal2(char * filename,int ** matrice_ballot, int row, int nbCandidate, int * imax, int * imax2, int * vote_max, int * vote_max2){

  int * tab = malloc((nbCandidate) * sizeof(int));
  
  for(i = 0; i < nbCandidate; i++){
    tab[i] = 0;
  }
  
  for(i = 0 ;i < row-1; i++){ 
    for(int j = 0;j < nbCandidate; j++){
      int val_courante = matrice_ballot[i][j];
      for(int k = 0; k < nbCandidate; k++){
        if(val_courante < matrice_ballot[i][k] && j != k){  
        tab[j] = tab[j] + 1;
       }
      }
    }
  }

  *vote_max = tab[0];
  *imax = 0;
  
  for(i = 0; i < nbCandidate; i++){
    if( tab[i] > *vote_max){
      *vote_max = tab[i];
      *imax = i;
    }
  }
  
  *vote_max2 = tab[0];
  *imax2 = 0;

  for(i = 0; i < nbCandidate; i++){
    if(tab[i] > *vote_max2 && i != *imax){
      *vote_max2 = tab[i];
      *imax2 = i;
    }
  }

  float sum = 0.0;

  for (i = 0; i < nbCandidate; i++)
    sum += tab[i];

  float score1 = (*vote_max)*100 / sum;
  float score2 = (*vote_max2)*100 / sum;

  int igagnant1 = *imax, igagnant2 = *imax2;

  char * g1 = vainqueur(filename, nbCandidate, &igagnant1);
  char * g2 = vainqueur(filename, nbCandidate, &igagnant2);

  g1[strcspn(g1, "\n")] = 0;
  g2[strcspn(g2, "\n")] = 0;

  printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %f%%\n",nbCandidate, row-1, g1, score1);

  printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %f%%\n",nbCandidate, row-1, g2, score2);  
 
 if (score1 <= 50.0 || score2 <= 50.0){
    ////////DEUXIEME TOUR///////////
    int ** mat = allocMatrix(2,2);
    
    for(i = 0; i < 2; i++){
      for(j = 0; j < 2; j++){
        mat[i][j] = 0;
      }
    }
      
   int tab1[100], tab2[100];

   for(i = 0; i < row - 1; i++){
    tab1[i] = matrice_ballot[i][*imax];
    tab2[i] = matrice_ballot[i][*imax2];
   }

   for(i = 0; i < row-1; i++){
    if( tab1[i] < tab2[i]){
      mat[0][1] += 1;
    }
    else if( tab1[i] > tab2[i])
      mat[1][0] += 1;
   }

    char * egal = "Egalité entre ";

    score1 = mat[0][1]*100/(mat[0][1]+mat[1][0]);
    score2 = mat[1][0]*100/(mat[0][1]+mat[1][0]);
    
    if (mat[0][1] > mat[1][0])
      printf("Mode de scrutin : uninominal à deux tours, tour 2, %d candidats, %d votants, vainqueur = %s, score = %f%%\n",nbCandidate, row-1, g1, score1);
    else if (mat[1][0] < mat[0][1])
      printf("Mode de scrutin : uninominal à deux tours, tour 2, %d candidats, %d votants, vainqueur = %s, score = %f%%\n",nbCandidate, row-1, g1, score2);
    else{
      printf("Mode de scrutin : uninominal à deux tours, tour 2, %d candidats, %d votants, vainqueur = egalité entre %s et %s\n",nbCandidate, row-1, g1, g2); 
    }
 }
 else{
  printf("Mode de scrutin : uninominal à deux tours, tour 2, %d candidats, %d votants, vainqueur = %s, score = %f%%\nCe candidat a plus de 50%% de voix, donc déclaré(e) vainqueure.", nbCandidate, row - 1, g1, score1);
 }
}

char * vainqueur(char * filename, int nbCandidate, int * imax){
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

  while (name != NULL && j < 4){
    name = strtok(NULL, ",");
    j++;
  }

  while (name != NULL && j >= 4){
    candidateName[i] = name;
    name = strtok(NULL, ",");
    i++;
  }
  
//  for(i = 0; i < nbCandidate; i++)
//    printf("%s\n", candidateName[i]);

  candidateName[*imax][strcspn(candidateName[*imax], "\n")] = 0;

//  for (i = 0; i < strlen(candidateName[*imax]); i++){
//    printf("%c", candidateName[*imax][i]);
//  }

  fclose(file);

  candidateName[*imax][strcspn(candidateName[*imax], "\n")] = 0;

  return candidateName[*imax]; 
}