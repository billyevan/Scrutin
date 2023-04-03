/**
 *@file scrutin.c
 *@author Evandion Brilliant KURNIADI
 */

#include "global.h"
#include <getopt.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void print_usage() {
	printf("Usage: scrutin -i <fichier csv> | -d <fichier csv> -o  <fichier txt> -m <méthode>\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	int option;
	int iflag = 0;
	int dflag = 0;
	int mflag = 1;
	int m = 0;

	char *csv = NULL;
	char *txt = NULL;
	char *methode = NULL;

	while ((option = getopt(argc, argv, "i:d:o:m:")) != -1) {
		switch (option) {
		case 'i':
			iflag = 1;
			csv = optarg;
			break;

		case 'd':
			dflag = true;
			csv = optarg;
			break;

		case 'o':
			txt = optarg;
			printf("Txt fichier %s", txt);
			break;

		case 'm':
			mflag = 0;
			m++;
			methode = optarg;
			break;

		case '?':
			if (optopt == 'i' || optopt == 'd' || optopt == 'o' ||
				optopt == 'm')
				print_usage();
			break;

		default:
			print_usage();
			break;
		}
	}

	if (iflag && dflag) {
		printf("Erreur: options -i et -d sont indépendants !\n");
		exit(EXIT_FAILURE);
	}

	else if (argc < 4) {
		print_usage();
	}

	else if (m != 1) {
		print_usage();
	}

	else if (iflag) { // Ballot

		if (strcmp(methode, "uni1") == 0) {
			int row = linecount(csv);
			int nbVotant = row - 1;

			int col = columncount(csv);
			int nbCandidateBallot = col - 4;

			int **matrice_ballot = allocMatrix(
				row, nbCandidateBallot); // allocation matrice pour le ballot
			result(csv, col, matrice_ballot); // transformation ballot en
											  // matrice

			int **matrice_duel_ballot =
				matduel_ballot(matrice_ballot, row, nbCandidateBallot);

			int imax, imax2, vote_max, vote_max2;
			uninominal1(csv, matrice_ballot, row, nbCandidateBallot);
		}

		else if (strcmp(methode, "uni2") == 0) {
			int row = linecount(csv);
			int nbVotant = row - 1;

			int col = columncount(csv);
			int nbCandidateBallot = col - 4;

			int **matrice_ballot = allocMatrix(
				row, nbCandidateBallot); // allocation matrice pour le ballot
			result(csv, col, matrice_ballot); // transformation ballot en
											  // matrice

			int **matrice_duel_ballot =
				matduel_ballot(matrice_ballot, row, nbCandidateBallot);

			int imax, imax2, vote_max, vote_max2;
			uninominal2(
				csv,
				matrice_ballot,
				row,
				nbCandidateBallot,
				&imax,
				&imax2,
				&vote_max,
				&vote_max2);
		}

		else if (strcmp(methode, "cm") == 0) {
			int row = linecount(csv);
			int nbVotant = row - 1;

			int col = columncount(csv);
			int nbCandidateBallot = col - 4;

			int **matrice_ballot = allocMatrix(
				row, nbCandidateBallot); // allocation matrice pour le ballot
			result(csv, col, matrice_ballot); // transformation ballot en
											  // matrice

			int **matrice_duel_ballot =
				matduel_ballot(matrice_ballot, row, nbCandidateBallot);

			Elementliste e;
			liste liste;
			createList(&liste);
			creerArcMinimax(&e, &liste, matrice_duel_ballot, nbCandidateBallot);
			minimax_ballot(csv, liste, nbCandidateBallot, row);
		}

		else if (strcmp(methode, "cs") == 0) {
			int row = linecount(csv);
			int nbVotant = row - 1;

			int col = columncount(csv);
			int nbCandidateBallot = col - 4;

			int **matrice_ballot = allocMatrix(
				row, nbCandidateBallot); // allocation matrice pour le ballot
			result(csv, col, matrice_ballot); // transformation ballot en
											  // matrice

			int **matrice_duel_ballot =
				matduel_ballot(matrice_ballot, row, nbCandidateBallot);

			schulze_ballot(csv, matrice_duel_ballot, nbCandidateBallot, row);
		}

		else if (strcmp(methode, "all") == 0) {
			int row = linecount(csv);
			int nbVotant = row - 1;

			int col = columncount(csv);
			int nbCandidateBallot = col - 4;

			// Uninominal 1
			int **matrice_ballot = allocMatrix(
				row, nbCandidateBallot); // allocation matrice pour le ballot
			result(csv, col, matrice_ballot); // transformation ballot en
											  // matrice

			int **matrice_duel_ballot =
				matduel_ballot(matrice_ballot, row, nbCandidateBallot);

			int imax, imax2, vote_max, vote_max2;
			uninominal1(csv, matrice_ballot, row, nbCandidateBallot);

			// Uninominal 2
			int **matrice_ballot2 = allocMatrix(
				row, nbCandidateBallot); // allocation matrice pour le ballot
			result(
				csv, col, matrice_ballot2); // transformation ballot en matrice

			int **matrice_duel_ballot2 =
				matduel_ballot(matrice_ballot2, row, nbCandidateBallot);

			int imax1, imax21, vote_max1, vote_max21;
			uninominal2(
				csv,
				matrice_ballot,
				row,
				nbCandidateBallot,
				&imax1,
				&imax21,
				&vote_max1,
				&vote_max21);

			// Minimax
			int **matrice_ballot3 = allocMatrix(
				row, nbCandidateBallot); // allocation matrice pour le ballot
			result(
				csv, col, matrice_ballot3); // transformation ballot en matrice

			int **matrice_duel_ballot3 =
				matduel_ballot(matrice_ballot3, row, nbCandidateBallot);

			Elementliste e;
			liste liste;
			createList(&liste);
			creerArcMinimax(&e, &liste, matrice_duel_ballot, nbCandidateBallot);
			minimax_ballot(csv, liste, nbCandidateBallot, row);

			// Schulze
			int **matrice_ballot4 = allocMatrix(
				row, nbCandidateBallot); // allocation matrice pour le ballot
			result(csv, col, matrice_ballot); // transformation ballot en
											  // matrice

			int **matrice_duel_ballot4 =
				matduel_ballot(matrice_ballot4, row, nbCandidateBallot);

			schulze_ballot(csv, matrice_duel_ballot, nbCandidateBallot, row);
		}

		else {
			print_usage();
		}
	}

	if (dflag) { // Matrice de duel
		if (strcmp(methode, "uni1") == 0) {
			printf("Erreur: Méthode uninominal à 1 tour est désactivée pour "
				   "une matrice de duel vu l'incompatibilité des données.");
			exit(EXIT_FAILURE);
		}

		else if (strcmp(methode, "uni2") == 0) {
			printf("Erreur: Méthode uninominal à 2 tour est désactivée pour "
				   "une matrice de duel vu l'incompatibilité des données.");
			exit(EXIT_FAILURE);
		}

		else if (strcmp(methode, "cm") == 0) {
			int nbCandidate = columncount(csv);

			int **matrix = allocMatrix(nbCandidate, nbCandidate);
			duelmatrix(csv, matrix);

			Elementliste e;
			liste liste;
			createList(&liste);
			creerArcMinimax(&e, &liste, matrix, nbCandidate);
			// dumpList(liste, stdout);
			minimax_duel(csv, liste, nbCandidate, nbCandidate);
		}

		else if (strcmp(methode, "cs") == 0) {
			int nbCandidate = columncount(csv);

			int **matrix = allocMatrix(nbCandidate, nbCandidate);
			duelmatrix(csv, matrix);

			schulze_duel(csv, matrix, nbCandidate, nbCandidate);
		}

		else if (strcmp(methode, "all") == 0) {
			int nbCandidate = columncount(csv);

			int **matrixM = allocMatrix(nbCandidate, nbCandidate);
			duelmatrix(csv, matrixM);

			// Méthode Minimax
			Elementliste e;
			liste liste2;
			createList(&liste2);
			creerArcMinimax(&e, &liste2, matrixM, nbCandidate);
			minimax_duel(csv, liste2, nbCandidate, nbCandidate);

			int **matrixS = allocMatrix(nbCandidate, nbCandidate);
			duelmatrix(csv, matrixS);

			// Méthode Schulze
			Elementliste e1;
			liste liste1;
			createList(&liste1);
			creerArcSchulze(&e1, &liste1, matrixS, nbCandidate);
			schulze_duel(csv, matrixS, nbCandidate, nbCandidate);
		}

		else {
			print_usage();
		}
	}

	return 0;
}