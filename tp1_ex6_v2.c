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
	int totalSize, size;
	int* values;
	
	if (argc != 2)
	{
		printf ("il faut donner un nombre\n");
		exit (1);
	}
	else
	{
		totalSize = atoi (argv[1]);
		size = totalSize / nb_proc;
		values = malloc (size * sizeof (int));
	}
	
	if (rang == 0)
	{
		values = (int*) malloc (totalSize * sizeof (int));
		for (int i = 0; i < totalSize; i++)
			values[i] = i;
		
		for (int i = 0; i < nb_proc; i++)
			MPI_Send (values + i * size, size, MPI_INT, i, i, MPI_COMM_WORLD);
	}
	MPI_Recv (values, size, MPI_INT, 0, rang, MPI_COMM_WORLD, &statut);
	for (int i = 0; i < size; i++)
		printf ("%d: j'ai recu %d du processus 0\n", rang, values[i]);
			
	code = MPI_Finalize();
	exit (0);
}
