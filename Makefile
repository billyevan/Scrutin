$(CC) = gcc
scrutin: scrutin.o condorcet.o elementliste.o lecture_csv.o liste.o sdd.o uninominale.o
	$(CC) scrutin.o condorcet.o elementliste.o lecture_csv.o liste.o sdd.o uninominale.o -o scrutin

scrutin.o: scrutin.c global.h
	$(CC) -c scrutin.c

condorcet.o: condorcet.c global.h
	$(CC) -c condorcet.c

elementliste.o: elementliste.c global.h elementliste.h
	$(CC) -c elementliste.c

lecture_csv.o: lecture_csv.c global.h
	$(CC) -c lecture_csv.c

liste.o: liste.c global.h liste.h
	$(CC) -c liste.c

sdd.o: sdd.c global.h
	$(CC) -c sdd.c

uninominale.o: uninominale.c global.h
	$(CC) -c uninominale.c


clean:
	rm *.o scrutin