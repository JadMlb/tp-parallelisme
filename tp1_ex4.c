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
	float diametre = 0;
	
	for (int i = -1; i <= 1; i += 2)
	{
		int to = (rang + i) % nb_proc;
		if (rang == 0 && to < 0)
			to = nb_proc - 1;
		MPI_Send (&valeur, 1, MPI_INT, to, tag, MPI_COMM_WORLD);
		printf ("%d: diffuse au voisin %d\n", rang, to);	
	}
	
	for (int i = -1; i <= 1; i += 2)
	{
		int from = (rang + i) % nb_proc;
		if (rang == 0 && from < 0)
			from = nb_proc - 1;
		MPI_Recv (&valeur, 1, MPI_INT, from, from, MPI_COMM_WORLD, &statut);
		printf ("%d: recu du voisin %d\n", rang, from);
	}
			
	code = MPI_Finalize();
	exit (0);
}
