#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv[])
{
	int rang, nb_proc, code, nb_valeur, taille, i;
	float somme, *valeurs, *donnees;
	MPI_Status statut;
	code = MPI_Init (&argc, &argv);
	code = MPI_Comm_size (MPI_COMM_WORLD, &nb_proc);
	code = MPI_Comm_rank (MPI_COMM_WORLD, &rang);
	nb_valeur = 32;
	taille = nb_valeur / nb_proc;
	donnees = (float*) malloc (taille * sizeof (float));
	
	if (rang == 0)
	{
		valeurs = (float*) malloc (nb_valeur * sizeof (float));
		for (i = 0; i < nb_valeur; i++)
			valeurs[i] = (float) (100 + i);
	}
	
	MPI_Scatter (valeurs, taille, MPI_FLOAT, donnees, taille, MPI_FLOAT, 0, MPI_COMM_WORLD);

	somme = 0;
	for (i = 0; i < taille; i++)
		somme += donnees[i];
	
	printf ("Moi le processus %d j'ai recu %.0f %.0f du processus 0 et la somme est %.0f\n", rang, donnees[0], donnees[taille - 1], somme);
	
	free (valeurs);
	free (donnees);

	code = MPI_Finalize();
	exit (0);
}
