#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv[])
{
	int rang, nb_proc, code, valeur, tag;
	int* valeurs;
	MPI_Status statut;
	code = MPI_Init (&argc, &argv);
	code = MPI_Comm_size (MPI_COMM_WORLD, &nb_proc);
	code = MPI_Comm_rank (MPI_COMM_WORLD, &rang);
	int n = 0;
	double t1, t2;
	
	if (argc != 2)
	{
		printf ("il faut donner un nombre");
		exit (1);
	}
	else
	{
		n = atoi (argv[1]);
		valeurs = (int*) malloc (n * sizeof (int));
		for (int i = 0; i < n; i++)
			valeurs[i] = i;
	}
	
	t1 = MPI_Wtime();
	
	if (rang == 0)
	{
		MPI_Send (valeurs, n, MPI_INT, 1, tag, MPI_COMM_WORLD);
		printf ("Moi, processus %d j'ai envoyé au processus 1\n", rang);
		t2 = MPI_Wtime();
		printf ("finished sending in: %f\n", t2 - t1);
	}
	else if (rang == 1)
	{
		MPI_Recv (valeurs, n, MPI_INT, 0, tag, MPI_COMM_WORLD, &statut);
		printf ("Received %d elements\n", sizeof (valeurs) / sizeof (valeurs[0]));
		for (int i = 0; i < n; i++)
		{
			printf ("Moi, processus %d j'ai recu %d du processus 0,\n", rang, valeurs[i]);
		}
		t2 = MPI_Wtime();
		printf ("finished receiving in: %f\n", t2 - t1);
	}
			
	code = MPI_Finalize();
	exit (0);
}
