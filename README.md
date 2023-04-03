# Scrutin
A program to determine the winner of a vote, written in C.
The interface is written in French.

To launch, launch the following commands:

$ make

$ scrutin -i [csv file] | -d ][csv file] -o  [txt file] -m [method]

This program reads a .csv file containing either the voters' ballot (the voter's data with their associated order of preference for each candidate) or a matrix of pairwise preferences, then determines the winner using the following methods:
 - Uninominal à un tour (single-round race) [As applied in the UK and Commonwealth countries]
 - Uninominal à deux tours (two-rounds race) [As applied in France]
 - (Condorcet) Minimax
 - (Condorcet) Schulze

The last two aforementioned Condorcet methods are used to better reflect the voters' voice and preferences as Nicolas de Caritat, marquis de Condorcet, pointed out in his "Essai sur l’application de l’analyse à la probabilité des décisions rendues à la pluralité des voix".

Finally, this project is part of my undergraduate Computer Science study (first semester of the 2nd year).
