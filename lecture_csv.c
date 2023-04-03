/**
 *@file lecture_csv.c
 *@author Evandion Brilliant KURNIADI
 */
#include "global.h"

char *multi_tok(char *input, char *delimiter) {
  static char *string;
  if (input != NULL)
    string = input;

  if (string == NULL)
    return string;

  char *end = strstr(string, delimiter);
  if (end == NULL) {
    char *temp = string;
    string = NULL;
    return temp;
  }

  char *temp = string;

  *end = '\0';
  string = end + strlen(delimiter);
  return temp;
}

int columncount(char * filename){
  char line[1024];
  
  FILE * file = fopen(filename, "r");
    
  if (file == NULL){
    printf("Erreur, impossible d'ouvrir le fichier.");
    exit(EXIT_FAILURE);
  }
  int dim = 0;
  
  char * heading = fgets(line, 1024, file);
  char * token_heading = multi_tok(heading, ",");

  while (token_heading != NULL) {
    //printf("%s\n", token_heading);
    token_heading = multi_tok(NULL, ",");
    dim++;
  }

  fclose(file);

  //
    file = fopen(filename, "r");
    
  if (file == NULL){
    printf("Erreur, impossible d'ouvrir le fichier.");
    exit(EXIT_FAILURE);
  }
  
  heading = fgets(line, 1024, file);
  token_heading = multi_tok(heading, ",");

  char ** tab_heading = malloc(dim * 100 * sizeof(char *));
  i = 0;

  while (token_heading != NULL) {
    tab_heading[i] = token_heading; i++;
    token_heading = multi_tok(NULL, ",");
  }
  return dim;
}

int linecount(char * filename){
  int count = 0;
  FILE * file = fopen(filename, "r");
  char ch;

   //read character by character and check for new line
   while((ch=fgetc(file))!=EOF) {
      if(ch=='\n')
        count++;
   }
  return count;
}

void content(char * filename, int dim);

void result(char * filename,int column, int ** mat_ballot){
  FILE * file = fopen(filename, "r");
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  i = 0;

  while ((read = getline(&line, &len, file)) != -1) {
    j = 0;
    char * ptr = strtok(line, ",");
    int n = 0;
    while(n < 4 && ptr != NULL){
      n++;
      ptr = strtok(NULL, ",");
    }

    if (i != 0){
      while(ptr != NULL && j != column )
      {
        mat_ballot[i-1][j] = atoi(ptr);
        int test = mat_ballot[i-1][j];
        //printf("%d ", test);
        j++;
        ptr = strtok(NULL, ",");
      }
//      printf("\n");
    }
  i++;
  }
}

// Convertir csv mat duel en matrice
void duelmatrix(char * filename, int ** matDuels){
  FILE * file = fopen(filename, "r");
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  i = 0;
  
  while ((read = getline(&line, &len, file)) != -1){
    j = 0;
    
    char * ptr = strtok(line, ",");

    if (i != 0)
    {
      while(ptr != NULL)
      {
        matDuels[i-1][j] = atoi(ptr);
        j++;
        ptr = strtok(NULL, ",");
      }
    }
    i++;
  }
}