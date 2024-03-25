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
	valeur = rang;
	tag = rang;
	// supposer que hypercube dim 3 et anneau dim 6
	int next[] = {1, 5, -1, -1, -1, 7, 2, 6}, prev[] = {2, 0, -1, -1, -1, 1, 7, 5};
	
	int to = next[rang];
	if (next[rang] > -1)
	{
		MPI_Send (&valeur, 1, MPI_INT, to, tag, MPI_COMM_WORLD);
		printf ("%d: diffuse au voisin %d\n", rang, to);
		to = prev[rang];
		MPI_Send (&valeur, 1, MPI_INT, to, tag, MPI_COMM_WORLD);
		printf ("%d: diffuse au voisin %d\n", rang, to);
	
		int from = prev[rang];
		MPI_Recv (&valeur, 1, MPI_INT, from, from, MPI_COMM_WORLD, &statut);
		printf ("%d: recu du voisin %d\n", rang, from);
		from = next[rang];
		MPI_Recv (&valeur, 1, MPI_INT, from, from, MPI_COMM_WORLD, &statut);
		printf ("%d: recu du voisin %d\n", rang, from);
	}

	code = MPI_Finalize();
	exit (0);
}
