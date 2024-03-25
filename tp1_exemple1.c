#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv[])
{
	int rang, nb_proc, code;
	code = MPI_Init (&argc, &argv);
	code = MPI_Comm_size (MPI_COMM_WORLD, &nb_proc);
	code = MPI_Comm_rank (MPI_COMM_WORLD, &rang);
	
	if (code != MPI_SUCCESS)
		printf ("Error\n");
	else
		printf ("je suis le procr %d parmi %d\n", rang, nb_proc);
	code = MPI_Finalize();
	exit (0);
}
