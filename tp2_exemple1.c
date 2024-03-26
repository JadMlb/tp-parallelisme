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
	if (rang == 0)
		valeur = 100;
	
	MPI_Bcast (&valeur, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf ("Moi le processus %d j'ai recu %d du processus 0\n", rang, valeur);

	code = MPI_Finalize();
	exit (0);
}
