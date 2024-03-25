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
	valeur = 1000;
	
	for (int i = 0; i < 10; i++)
	{
		if (rang == 0)
		{
			MPI_Send (&valeur, 1, MPI_INT, 1, tag + i, MPI_COMM_WORLD);
			printf ("%d: Ping %d\n", rang, i);
			MPI_Recv (&valeur, 1, MPI_INT, 1, tag + i, MPI_COMM_WORLD, &statut);
			printf ("%d: Recu Pong de %d du processus 1\n", rang, valeur);
			valeur += i;
		}
		else if (rang == 1)
		{
			MPI_Recv (&valeur, 1, MPI_INT, 0, tag + i, MPI_COMM_WORLD, &statut);
			printf ("%d: Recu Ping de %d du processus 0\n", rang, valeur);
			MPI_Send (&valeur, 1, MPI_INT, 0, tag + i, MPI_COMM_WORLD);
			printf ("%d: Pong %d\n", rang, i);
			
			valeur += i;
		}
	}
			
	code = MPI_Finalize();
	exit (0);
}
