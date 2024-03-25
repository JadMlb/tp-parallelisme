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
	double t1, t2;
	
	if (argc != 2)
	{
		printf ("il faut donner un nombre");
		exit (1);
	};
	
	t1 = MPI_Wtime();
	if (rang == 0)
	{
		for (int i = 0; i < atoi (argv[1]); i++)
		{
			MPI_Send (&valeur, 1, MPI_INT, 1, tag + i, MPI_COMM_WORLD);
			printf ("Moi, processus %d j'ai envoyé %d au processus 1, a l'iteration %d\n", rang, valeur, i);
			valeur += i;
		}
		t2 = MPI_Wtime();
		printf ("Envoye en: %f\n", t2 - t1);
	}
	else if (rang == 1)
	{
		for (int i = 0; i < atoi (argv[1]); i++)
		{
			MPI_Recv (&valeur, 1, MPI_INT, 0, tag + i, MPI_COMM_WORLD, &statut);
			printf ("Moi, processus %d j'ai recu %d du processus 0, a l'iteration %d\n", rang, valeur, i);
			valeur += i;
		}
		t2 = MPI_Wtime();
		printf ("Recu en: %f\n", t2 - t1);
	}
			
	code = MPI_Finalize();
	exit (0);
}
