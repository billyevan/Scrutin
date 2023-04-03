/**
 *@file global.h
 *@author Evandion Brilliant KURNIADI
 */
#define _GNU_SOURCE
#include <sys/types.h>

#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include "liste.h"
#include "elementliste.h"

#define MAXCANDIDATE 30

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAXI(a,b) (((a)>(b))?(a):(b))

int i, j;

/**
 *@brief Traitement de séparation d'une ligne avec un délimiteur
 *@param[in] char *input
 *@param[in] char *delimiter
 *@return char*
 */
char *multi_tok(char * input, char * delimiter);

/**
 *@brief Compter le nombre de colonne dans un fichier
 *@param[in] char * filename
 *@return int
 */
int columncount(char * filename);

/**
 *@brief Compter le nombre de ligne dans un fichier
 *@param[in] char* filename
 *@return int
 */
int linecount(char* filename);

/**
 *@brief Mettre le resultat de vote d'un ballot à une matrice
 *@param[in] char * filename
 *@param[in] int column
  *@param[in] int ** mat_ballot
 *@return void
 */
void result(char * filename, int column, int ** mat_ballot);

/**
 *@brief Récupérer la matrice de duel à partir d'un fichier csv en le mettan dans une matrice
 *@param[in] char * filename
 *@param[in]  int ** matDuels
 *@return void
 */
void duelmatrix(char * filename, int ** matDuels);

/**
 *@brief L'allocation de mémoire pour une matrice
 *@param[in] int row
 *@param[in] int col
 *@return int **
 */
int ** allocMatrix(int row, int col);

/**
 *@brief Générer la matrice des duels à partir du résultat d'un fichier de csv contenant le ballot
 *@param[in] int ** mat_ballot
 *@param[in]  int row
 *@param[in]  int nbCandidate
 *@return int **
 */
int ** matduel_ballot(int ** mat_ballot, int row, int nbCandidate);

/**
 *@brief Calculer le gagnant avec la méthode uninominal à 1 tour, puis afficher le résultat sur stdout
 *@param[in] char * filename
 *@param[in] int ** mat_ballot
 *@param[in] int row
 *@param[in] int nbCandidate
 *@return void
 */
void uninominal1(char * filename, int ** mat_ballot, int row, int nbCandidate);

/**
 *@brief Calculer le gagnant avec la méthode uninominal à 2 tour, ensuite afficher le résultat sur stdout
 *@param[in] char * filename
 *@param[in]  int ** matrice_ballot
 *@param[in]  int row
 *@param[in]  int nbCandidate
 *@param[in]  int * imax
 *@param[in]  int * imax2
 *@param[in]  int * vote_max
 *@param[in]  int * vote_max2
 *@return void
 */
void uninominal2(char * filename, int ** matrice_ballot, int row, int nbCandidate, int * imax, int * imax2, int * vote_max, int * vote_max2);

/**
 *@brief Récuperer le nom du vainqueur en faisant un tableau contenant le nom de tous les candidats, trouver l'indice où se trouve la valeur corespondante au vainqueur, utiliser cet indice dans le tableu pour trouver le nom du candidat correspondante. Ceci est pour un ballot car il faut ignorer les quatre premières colonnes administratives.
 *@param[in]  char * filename
 *@param[in]  int * imax
 *@param[in]  int nbCandidate
 *@return char * 
 */
char * vainqueur(char * filename, int nbCandidate, int * imax);

/**
 *@brief Récuperer le nom du vainqueur en faisant un tableau contenant le nom de tous les candidats, trouver l'indice où se trouve la valeur corespondante au vainqueur, utiliser cet indice dans le tableu pour trouver le nom du candidat correspondante. Ceci est pour une matrice de duel dont la première ligne contient déjà le nom des candidats
 *@param[in] char * filename
 *@param[in]  int nbCandidate
 *@param[in]  int *imax
 *@return char * 
 */
char * vainqueurDuel(char * filename, int nbCandidate, int * imax);
//char * vainqueurMinimax(char * filename, int nbCandidate, int * imax);

/**
*@brief Creer des arcs à partir de la matrice des duels
*@param[in] t_arc_p * Elementliste
*@param[in] liste * liste
*@param[in] int ** mat_duel
*@param[in] int nbCandidate
*/
void creerArcMinimax(t_arc_p * Elementliste, liste * liste, int ** mat_duel, int nbCandidate);

/**
*@brief Creer des arcs à partir de la matrice des duels pour le calcule de la méthode Schulze
*@param[in] Elementliste * e
*@param[in] liste * liste
*@param[in] int ** mat_duel
*@param[in] int nbCandidate
*/
void creerArcSchulze(Elementliste * e, liste * liste, int ** mat_duel, int nbCandidate);

/**
*@brief trouver le vainqueur selon la methode de Condorcet minimax d'une matrice de duel, ensuite afficher sur l'écran le résultat
*@param[in] char * filename
*@param[in] liste liste
*@param[in] int nbCandidate
*@param[in] int row
*/
void minimax_duel(char * filename,liste liste, int nbCandidate, int row);


/**
*@brief Trouver le vainqueur selon la methode de Condorcet minimax d'un ballot, puis afficher le résultat sur l'écran le résultat
*@param[in] char * filename
*@param[in] liste liste
*@param[in] int nbCandidate
*@param[in] int row
*/
void minimax_ballot(char * filename,liste liste, int nbCandidate, int row);

/**
*@brief Application de la methode de Condorcet Schulze pour trouver le vainqueur à partir d'une matrice de duel. Le résultat est ensuite affiché sur l'écran.
*@param[in] char * filename
*@param[in] int **mat_duel
*@param[in] int nbCandidate
*@param[in] int row)
*/
void schulze_duel(char * filename,int **mat_duel, int nbCandidate, int row);

/**
*@brief Application de la methode de Condorcet Schulze pour trouver le vainqueur à partir d'un ballot. Le résultat est ensuite affiché sur l'écran.
*@param[in] char * filename
*@param[in] int **mat_duel
*@param[in] int nbCandidate
*@param[in] int row)
*/
void schulze_ballot(char * filename,int **mat_duel, int nbCandidate, int row);

#endif