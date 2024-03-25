#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv[])
{
	int rang, nb_proc, code, valeur, tag;
	MPI_Status statut;
	code = MPI_Init (&argc, &argv);
	code = MPI_Comm_size (MPI_COMM_WORLD, &nb_proc);
	code = MPI_Comm_rank (MPI_COMM_WORLD, &rang);
	valeur = 0;
	
	tag = rang;
	
	if (rang == 0)
	{
		for (int i = 1; i < nb_proc; i++)
		{
			MPI_Recv (&valeur, 1, MPI_INT, i, tag + i, MPI_COMM_WORLD, &statut);
			printf ("%d: Recu \"pret\" du processus %d\n", rang, i);
		}
		
		valeur = 1;
		for (int i = 1; i < nb_proc; i++)
		{
			MPI_Send (&valeur, 1, MPI_INT, i, tag + i, MPI_COMM_WORLD);
			printf ("%d: Envoye \"sync\" au processus %d\n", rang, i);
		}
	}
	else
	{
		MPI_Send (&valeur, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
		printf ("%d: Envoye \"pret\" au processus 0\n", rang);
		MPI_Recv (&valeur, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &statut);
		printf ("%d: Recu \"sync\" du processus 0\n", rang);
	}
			
	code = MPI_Finalize();
	exit (0);
}
