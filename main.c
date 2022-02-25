/******************************************/
/* Hasan BASBUNAR                          */
/* Dernière modification   
    Le  25/02/2022                         */
/******************************************/

#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include "functions.h"

//-------------------------------------------
void    initialiseTab   ();
void    swap            (int *x, int *y);
void    trouverPoids    (int *a);
void    permute         (int *a, int l, int r);
int     vectorFind      ();
//--------------------------------------------

double cpu_boucle;
Graphe G = NULL;
clock_t t1, t2;
int n, m, err;
int completed[777];
int poids=0;

int main()
{
    srand((unsigned int)time(NULL));
    int choixFichier;
    int choix = 0;
    int choix2 = 0;
    int ameliorer = 1;
    int choixFinal = 1;

    char *nom = malloc( 30 * sizeof(char));
    int **copieDeLaCopie    = malloc(sizeof(int *) * 777);
    int *memoireListe       = malloc(777 * sizeof(int));
    int *listeVisite        = malloc(777 * sizeof(int));
    int **copie             = malloc(sizeof(int *) * 777);


    for (int abc = 0; abc < 777; abc++)
    {
        copieDeLaCopie[abc] = malloc(sizeof(int) * 777);
        copie[abc]          = malloc(sizeof(int) * 777);
    }

    do
    {
        do
        {
            printf("Entrez numero de fichier : \n");
            printf("10, 11 ,12 ,13 ,14 ,15 ,16 ,17 ,18 ,19 ,20 ,25 ,50 ,100 ,150 ,200 ,300 ,400 ,500 ,777\n");
            scanf("%d", &choixFichier);

            switch(choixFichier)
            {
                case 10: nom="communes_10.txt"  ; break;      case 11: nom="communes_11.txt"    ; break;
                case 12: nom="communes_12.txt"  ; break;      case 13: nom="communes_13.txt"    ; break;
                case 14: nom="communes_14.txt"  ; break;      case 15: nom="communes_15.txt"    ; break;
                case 16: nom="communes_16.txt"  ; break;      case 17: nom="communes_17.txt"    ; break;
                case 18: nom="communes_18.txt"  ; break;      case 19: nom="communes_19.txt"    ; break;
                case 20: nom="communes_20.txt"  ; break;      case 25: nom="communes_25.txt"    ; break;
                case 50: nom="communes_50.txt"  ; break;      case 100: nom="communes_100.txt"  ; break;
                case 150: nom="communes_150.txt"; break;      case 200: nom="communes_200.txt"  ; break;
                case 300: nom="communes_300.txt"; break;      case 400: nom="communes_400.txt"  ; break;
                case 500: nom="communes_500.txt"; break;      case 777: nom="communes_777.txt"  ; break;
                default : printf("Ce fichier nexiste pas !\n");                                   break;
            }
            err = lire_data(nom, &G, &n, &m);
        }
        while(choixFichier != 10 && choixFichier != 11 && choixFichier != 12 && choixFichier != 13 && choixFichier != 14
              && choixFichier != 15 && choixFichier != 16 && choixFichier != 17 && choixFichier != 18 && choixFichier != 19
              && choixFichier != 20 && choixFichier != 25 && choixFichier != 50 && choixFichier != 100 && choixFichier != 150
              && choixFichier != 200 && choixFichier != 300 && choixFichier != 400 && choixFichier != 500 && choixFichier != 777
              && err == 0 );


        do
        {
            printf("\n ----------- M E N U ------------\n");
            printf("|  1 - Heuristique aleatoire     |\n|  2 - Heuristique du PPV        |\n|  5 - Brute Force               |\n");
            printf(" --------------------------------\n");
            scanf("%d", &choix);
        } while (choix != 5 && choix != 1 && choix != 2);
        if (choix == 1)
        {
            do
            {
                printf("\n --------------------------- Choix ? --------------------------\n");
                printf("| 1 - Heuristique aleatoire par permutation                    |\n| 2 - Heuristique generant aleatoirement des listes de visites |\n");
                printf(" --------------------------------------------------------------\n");
                scanf("%d", &choix2);
            } while (choix2 != 1 && choix2 != 2);
            if (choix2 == 1)
            {

                heuristiqueAleatoireParPermutation(G,listeVisite,n);

                do
                {
                    printf("\n ---------------- Ameliorer ? --------------------------------\n");
                    printf("| 1 - Ameliorer avec heuristique de decroisement (recommande) |\n| 0 - ne pas ameliorer                                        |\n -------------------------------------------------------------\n");
                    scanf("\n%d", &ameliorer);
                } while (ameliorer != 1 && ameliorer != 0);
                if(ameliorer == 1) choix = 6;
            }
            else
            {
                initialiseTableau(listeVisite,n,-1);


                heuristiqueAleatoire(G,listeVisite,n);
                do
                {
                    printf("\n ---------------- Ameliorer ? --------------------------------\n");
                    printf("| 1 - Ameliorer avec heuristique de decroisement (recommande) |\n| 0 - ne pas ameliorer                                        |\n -------------------------------------------------------------\n");
                    scanf("%d", &ameliorer);
                } while (ameliorer != 1 && ameliorer != 0);
                if(ameliorer == 1) choix = 6;

            }


        }
        if(choix == 2)
        {
            initialiseTableau(listeVisite,n,-1);
            faireUneCopieDuGraphe(G,copie,n);
            faireUneCopieDuGraphe(G,copieDeLaCopie,n);
            initialiseGrapheAvecSommets(copieDeLaCopie,n);
            trieGraphe(copie,copieDeLaCopie,n);
            printf("----- Heuristique du plus proche voisin : ----- \n\n");

            t1 = clock();
            printf("nombre de ticks d horloge avant la boucle : %lu\n", t1);

            int reponse  = heuristiqueDuPlusProcheVoisin(G,copie,copieDeLaCopie,listeVisite,n,0);

            t2 = clock();
            printf("nombre de ticks d'horloge apres la boucle : %lu\n", t2);
            printf("\ndistance trouve = %d km.\npour la liste : ",reponse);
            affiche(listeVisite,n);

            cpu_boucle = (double)(t2-t1)/(double)(CLOCKS_PER_SEC);
            printf("temps cpu de la boucle en secondes %f\n", cpu_boucle);

            do
            {
                printf("\n");
                printf("7 - heuristique tabou \n3 - essayer tous les sommets de depart possibles (recommande) \n2 - Ameliorer avec heuristique de decroisement\n1 - Ameliorer avec heuristique dechange de sommets\n0 - ne pas ameliorer\n");
                scanf("%d", &ameliorer);
            } while (ameliorer != 7 && ameliorer != 3 && ameliorer != 2 && ameliorer != 1 && ameliorer != 0);
            if(ameliorer == 1) choix = 3;
            else if(ameliorer == 3) choix = 4;
            else if(ameliorer == 2) choix = 6;
            else if(ameliorer == 7) choix = 7;
        }
        if(choix == 5)
        {
            printf("---------- Brute Force : ----------\n");

            t1 = clock();
            printf("nombre de ticks d'horloge avant la boucle : %lu\n", t1);

            initialiseTab();
            poids = calculerKmParcouru(G,completed,n);
            vectorFind();
            printf("\nPlus court chemin : %d km",poids);

            t2 = clock();
            printf("nombre de ticks d horloge apres la boucle : %lu\n", t2);
            cpu_boucle = (double)(t2-t1)/(double)(CLOCKS_PER_SEC);
            printf("temps cpu de la boucle en secondes %f\n", cpu_boucle);
        }
        if(choix == 4)
        {
            printf("essai PPV avec tous les sommets de depart : \n");
            t1 = clock();
            printf("nombre de ticks d'horloge avant la boucle : %lu\n", t1);

            essayerTousLesSommetsDeDepartsPourPPV(G,copie,copieDeLaCopie,listeVisite,n);

            t2 = clock();
            printf("nombre de ticks d horloge apres la boucle : %lu\n", t2);
            cpu_boucle = (double)(t2-t1)/(double)(CLOCKS_PER_SEC);
            printf("temps cpu de la boucle en secondes %f\n", cpu_boucle);
            do
            {
                printf("\n");
                printf("1 - Ameliorer avec heuristique de decroisement de deux arretes\n0 - ne pas ameliorer\n");
                scanf("%d", &ameliorer);
            } while (ameliorer != 1 && ameliorer != 0);
            if(ameliorer == 1) choix = 6;
        }

        if (choix == 6)
        {
            printf("-------------- Heuristique de decroisement de deux arretes ---------------------\n");
            t1 = clock();
            printf("nombre de ticks d horloge avant la boucle : %lu\n", t1);

            heuristiqueDeDecroismentDeDeuxArretes(G,listeVisite,n);
            t2 = clock();
            printf("liste : \n");
            affiche(listeVisite,n);
            printf("nombre de ticks d horloge apres la boucle : %lu\n", t2);
            cpu_boucle = (double)(t2-t1)/(double)(CLOCKS_PER_SEC);
            printf("temps cpu de la boucle en secondes %f\n", cpu_boucle);
            printf("-------------- FIN heuristique de decroisement de deux arretes ---------------------\n");
            do
            {
                printf("\n");
                printf("1 - Ameliorer avec heuristique dechange de deux sommets\n0 - ne pas ameliorer\n");
                scanf("%d", &ameliorer);
            } while (ameliorer != 1 && ameliorer != 0);
            if(ameliorer == 1) choix = 3;
        }

        if (choix == 3)
        {
            t1 = clock();
            printf("nombre de ticks d horloge avant la boucle : %lu\n", t1);

            heuristiqueDechangeDeDeuxSommetsPPV(G,listeVisite,n);

            t2 = clock();
            printf("nombre de ticks d horloge apres la boucle : %lu\n", t2);

            printf("liste : \n");
            affiche(listeVisite,n);

            cpu_boucle = (double)(t2-t1)/(double)(CLOCKS_PER_SEC);
            printf("temps cpu de la boucle en secondes %f\n", cpu_boucle);

        }
        if (choix == 7)
        {
            t1 = clock();
            printf("nombre de ticks d horloge avant la boucle : %lu\n", t1);

            tabou(G,listeVisite,n);

            t2 = clock();
            printf("nombre de ticks d horloge apres la boucle : %lu\n", t2);

            printf("apres echange de deux sommets : \n");
            affiche(listeVisite,n);

            cpu_boucle = (double)(t2-t1)/(double)(CLOCKS_PER_SEC);
            printf("temps cpu de la boucle en secondes %f\n", cpu_boucle);

        }

        do
        {
            printf("\n --- Voulez vous continuer ? ---\n|  1 - continuer                |\n|  0 - quitter                  |\n -------------------------------\n");
            scanf("%d",&choixFinal);
        } while (choixFinal != 1 && choixFinal != 0);

    } while (choixFinal == 1);
    for (int boucle = 0; boucle < 777; boucle++)
    {
        free(copie[boucle]);
        free(copieDeLaCopie[boucle]);
    }
    free(copie);
    free(copieDeLaCopie);
    free(listeVisite);
    free(memoireListe);
    free(nom);

    printf("Au revoir !\n\n");

    return 0;
} // FIN MAIN

//---------------------------------- FONCTIONS BRUTE FORCE ---------------------------------------

void initialiseTab()
{
    int i;
    for(i=0; i<n; i++)
    {
        completed[i] = i;
    }
}

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void trouverPoids(int *a)
{
    int i;
    int costAux = 0;
    for(i=0; i < n; i++)
    {
        if(i == n-1)
        {
            costAux = costAux + G[a[i]][a[0]];
        }
        else
        {
            costAux = costAux + G[a[i]][a[i+1]];
        }
    }

    if(costAux < poids)
    {
        poids = costAux;
        printf("Nouveau chemin plus court de [ %d ] km trouve ! \n",poids);
    }

}


void permute(int *a, int l, int r)
{
    int i;
    if (l == r)
    {
        trouverPoids(a);
    }
    else
    {
        for (i = l; i <= r; i++)
        {
            swap((a+l), (a+i));
            permute(a, l+1, r);
            swap((a+l), (a+i));
        }
    }
}

int vectorFind()
{
    int arr[n];
    int nb = sizeof(arr)/sizeof(arr[0]);
    int i = 0;
    for(i=0;i<n; i++)
    {
        arr[i] = completed[i];
    }
    permute(arr, 0, nb-1);
    return 0;
}
//--------------------------FIN-------------------------------------------------------------