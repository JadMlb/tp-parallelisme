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
	int* values = malloc (5 * sizeof (int));
	
	if (argc != 2)
	{
		printf ("il faut donner un nombre\n");
		// exit (1);
	};
	
	if (rang == 0)
	{
		values = (int*) malloc (10 * sizeof (int));
		for (int i = 0; i < 10; i++)
			values[i] = i;
		
		MPI_Send (values, 5, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Send (values + 5, 5, MPI_INT, 2, 2, MPI_COMM_WORLD);
	}
	else
	{
		MPI_Recv (values, 5, MPI_INT, 0, rang, MPI_COMM_WORLD, &statut);
		for (int i = 0; i < 5; i++)
			printf ("%d: j'ai recu %d du processus 0\n", rang, values[i]);
	}
			
	code = MPI_Finalize();
	exit (0);
}
