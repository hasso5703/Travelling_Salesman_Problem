#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "functions.h"

//---------------  F O N C T I O N S  D' A F F I C H A G E  -------------------------------------------------------------


void affiche(int *t, int taille)
{   
    printf("\n\n");
    for(int i = 0; i < taille; i++) printf("%5d", t[i]);
    printf("\n\n");
}


//----------------------------------------------------------------------------------------------------------------------------------------

//------------------------- H E U R I S T I Q U E   A L E A T O I R E ---------------------------------------------------------------------

void heuristiqueAleatoireParPermutation(Graphe G,int *tabAPermut, int taille)
{
    int poids = 0, poids2 = 0;
    int tab[taille];
    for (int i = 0; i < taille; i++) {
        tabAPermut[i]=i;
        tab[i]=tabAPermut[i];
    }
    poids2 = 99999999;
    int tmp;
    printf("Entrez le temps de recherche en secondes :\n");
    scanf("%d",&tmp);
    clock_t delai = tmp * CLOCKS_PER_SEC;
    clock_t start = clock();
    while ((clock() - start)<delai){

        permut(tab, taille);
        poids = calculerKmParcouru(G,tab,taille);
        if (poids<poids2)
        {
            poids2 = poids;
            for (int j = 0; j < taille; j++)
            {
                tabAPermut[j]=tab[j];
            }
        }

    }

    printf("poids minimum trouve = %d en %d secondes\npour la liste : ",poids2,tmp);
    affiche(tabAPermut,taille);
}


void heuristiqueAleatoire(Graphe g, int *tab, int taille) // autre facon
{
    int minimum = 10000000;
    int optimal;
    int tableau[taille];
    int tmp;
    printf("Entrez le temps de recherche en secondes :\n");
    scanf("%d",&tmp);
    clock_t delai = tmp * CLOCKS_PER_SEC;
    clock_t start = clock();
    while ((clock() - start)<delai) {
        genererListeAleatoire(taille, tableau);
        optimal = calculerKmParcouru(g, tableau, taille);
        if (optimal < minimum) {
            minimum = optimal;
            for (int i = 0; i < taille; ++i) {
                tab[i] = tableau[i];
            }

        }
    }
    
    printf("Le minimum trouvé pour %d sommets = %d km apres %d secondes de generation de listes aleatoires.\nliste : ",taille,minimum,tmp);
    affiche(tableau,taille);
}

void genererListeAleatoire(int taille, int *tab)  // idee : creer une liste de nombre de 0 a n puis piocher dedans au hasard                                                        
{                                                       // enlever les nombres deja present dans la listevisite de la liste a piocher
    initialiseTableau(tab,taille,-1);
    while(tab[taille-1] == -1)
    {
        verifSiDejaVisiteEtAjoutDansListe(tab, genereNombreAleatoire(taille), taille);
    }
}

int genereNombreAleatoire(int valeurMax)
{
    return rand() % valeurMax;
}



//----------------------------------------------------------------------------------------------------------------------------------------

//------------------- F O N C T I O N S  C O M M U N E S ---------------------------------------------------------------------------------

int calculerKmParcouru(Graphe g, int *tableau, int tailleTab){

    int compteurKilometrique = 0;
    for (int i = 0; i < tailleTab-1; i++) 
    {
        compteurKilometrique+=g[tableau[i]][tableau[i+1]];
    }
    compteurKilometrique += g[tableau[tailleTab-1]][tableau[0]];
    return compteurKilometrique;
}

void verifSiDejaVisiteEtAjoutDansListe(int *tab,int nombre,int taille)
{
    int j = 0;
    int visite = 0;
    for (int i = 0; i < taille; i++)
    {
        if (nombre == tab[i])
        {
            visite = 1;
            j = i;
            i = taille;
        }
        else if (tab[i] == -1)
        {
            j=i;
            i = taille;
        }
    }
    if (visite == 0)
    {
        tab[j]=nombre;
    }
}

int verifSiDejaVisite(int *tab,int nombre,int taille)
{
    int visite = 0;
    for (int i = 0; i < taille; i++)
    {
        if (nombre == tab[i])
        {
            visite = 1;
            i = taille;
        }
        else if (tab[i] == -1)
        {
            i = taille;
        }
    } 
    return visite;
}

// idée : utiliser static int variable pour savoir ou on en est dans le tableau
// et directement mettre la valeur dans cet emplacement sans entrer dans le for
void addInvisitedList(int *tab, int sommet, int n)
{                                           
    for (int i = 0; i < n; i++) 
    {
        if (tab[i] == -1)
        {
            tab[i] = sommet;
            i = n;
        }
    }
}

void initialiseTableau(int *tab, int taille, int valeur)
{
    for (int abi = 0; abi < taille; abi++)
    {
        tab[abi]=valeur;
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------

//------------------------- H E U R I S T I Q U E  D U  P L U S  P R O C H E  V O I S I N -------------------------------------------------

int heuristiqueDuPlusProcheVoisin(Graphe G, int **tab2dim, int **tab2dim2, int *tableau , int taille, int noSommetDepart)
{
    addInvisitedList(tableau,noSommetDepart,taille);
    genererListePlusProcheVoisin(tab2dim2,tableau,taille);
    return calculerKmParcouru(G,tableau,taille);
}

void faireUneCopieDuGraphe(Graphe g, int **tab, int taille)
{
    for (int z = 0; z < taille; z++) for (int x = 0; x < taille; x++) tab[z][x] = g[z][x];
}

void initialiseGrapheAvecSommets(int **tab, int taille)
{
    for (int i = 0; i < taille; i++) for (int j = 0; j < taille; j++) tab[i][j]=j;
}

void trieGraphe(int **graphe, int **graphe2, int taille)
{
    for (int i = 0; i < taille; i++)
        for (int j = 0; j < taille; j++) {
            int hist = 0;
            for (int k = j + 1; k < taille; k++)
                if (graphe[i][j] >= graphe[i][k]) {
                    hist = graphe[i][k];
                    graphe[i][k] = graphe[i][j];
                    graphe[i][j] = hist;
                    hist = graphe2[i][k];
                    graphe2[i][k] = graphe2[i][j];
                    graphe2[i][j] = hist;
                }
        }
}

void genererListePlusProcheVoisin(int **tab2dim ,int *tab, int taille)
{
    int i, j;
    for (i = tab[0]; i < taille; i++)
    {
        for (j = 1; j < taille; j++)
        {   

            if (verifSiDejaVisite(tab,tab2dim[i][j],taille) == 0)
            {
                addInvisitedList(tab,tab2dim[i][j],taille);
                i = (tab2dim[i][j]-1);
                j = taille;
            }
        }   
    }
}

void essayerTousLesSommetsDeDepartsPourPPV(Graphe G, int **tab2dim, int **tab2dim2, int *tableau , int taille)
{
    int km, km2 = 10000000;
    int liste[taille];
    for (int i = 1; i < taille; i++)
    {
        initialiseTableau(liste,taille,-1);
        km = heuristiqueDuPlusProcheVoisin(G,tab2dim,tab2dim2,liste,taille,i);
        if (km < km2)
        {
            km2 = km;
            for (int j = 0; j < taille; ++j) tableau[j]=liste[j];
        }

    }
    printf("\ndistance minimum trouve = [%d]\n liste : ",km2);
    affiche(tableau,taille);
}


//-----------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------- H E U R I S T I Q U E  D' E C H A N G E  D E  D E U X  S O M M E T S ----------------------------------------------


void heuristiqueDechangeDeDeuxSommetsPPV(Graphe g,int *tableau , int taille)
{
    int tableau2[taille];
    for (int k = 0; k < taille ; k++) tableau2[k]=tableau[k];
    int km = calculerKmParcouru(g,tableau,taille), km2;
    int kilom = km;
    int memoire = -1;
    for (int i = 0; i < taille; i++) {
        for (int j = i+1; j < taille; j++) {
            memoire = tableau2[i];
            tableau2[i] = tableau2[j];
            tableau2[j] = memoire;
            km2 = calculerKmParcouru(g,tableau2,taille);
            if(km2 < km){
                km = km2;
                for (int k = 0; k < taille ; k++) tableau[k]=tableau2[k];
            }
            for (int k = 0; k < taille ; k++) tableau2[k]=tableau[k];
        }

    }
    if (kilom == km) printf("\non n'a pas pu ameliorer !\n");
    else printf("\non a trouve un chemin plus court = [%d] km !\n",km);
}

void heuristiqueDeDecroismentDeDeuxArretes(Graphe g, int *tab, int taille)
{
    int kilometre = 0, kilometre2 = 0;
    kilometre = calculerKmParcouru(g,tab,taille);
    int kilom = kilometre;
    int i, j, k, l, memoire, memoire2;
    int tab2[taille];

    for (int m = 0; m < taille; m++)
    {
        tab2[m] = tab[m];
    }
    for (i = 0; i < taille-1; i+=2)
    {
        j=i+1;
        for (k = 0; k < taille-1; k++)
        {
            l=k+1;
            if (k != i)
            {
                memoire = tab2[j];
                tab2[j]=tab2[l];
                memoire2 = tab2[k];
                tab2[k]=memoire;
                tab2[l]=memoire2;
                kilometre2 = calculerKmParcouru(g,tab2,taille);
                if (kilometre2 < kilometre)
                {
                    kilometre = kilometre2;
                    for (int o = 0; o < taille; o++)
                    {
                        tab[o]=tab2[o];
                    }
                }
            }
            for (int n = 0; n < taille; n++)
            {
                tab2[n] = tab[n];
            }
        }

    }
    if (kilom == kilometre) printf("On n'a pas pu améliorer !");
    else printf("On a trouve un plus court chemin : [%d] km\nliste :", kilometre);
}

void heuristiqueDechangeDeDeuxSommetsPPVTabou(Graphe g,int *tableau , int taille)
{
    printf("debut tabou : \n");
    affiche(tableau,taille);
    int km = calculerKmParcouru(g,tableau,taille);
    printf("km avant = %d\n",km);
    int tableau2[taille];  // tableau sur lequel on va travailler
    for (int k = 0; k < taille ; k++) tableau2[k]=tableau[k];
    int tableau3[taille]; // tableau
    initialiseTableau(tableau3,taille,-1);
    int tableau4[taille]; // tablau qui contiendra les numeros de sommets
    for (int z = 0; z < taille; z++)
    {
        tableau4[z]= z;
    }
    int liste[taille-1][taille];  // tbaleau a deux dimensions ou on va stocker les chemins générés pour chaque etapes
    int km2;

    int memoire = -1;
    for (int i = 0; i < taille-1; i++)
    {
        for (int j = i+1; j < taille; j++)
        {
            memoire = tableau2[i];
            tableau2[i] = tableau2[j];
            tableau2[j] = memoire;
            km2 = calculerKmParcouru(g,tableau2,taille);
            for(int k = 0; k < taille; k++)
            {
                liste[i][k] = tableau2[k];
            }
            addInvisitedList(tableau3,km2,taille);
            for (int k = 0; k < taille ; k++) tableau2[k]=tableau[k];
        }

    }
    for (int y = 0; y < taille-1; y++)
    {
        for (int x = y+1; x < taille; x++)
        {
            if (tableau3[y]>tableau3[x])
            {
                int mem = tableau3[y];
                tableau3[y]=tableau3[x];
                tableau3[x]=mem;
                int mem2 = tableau4[y];
                tableau4[y]=tableau4[x];
                tableau4[x]=mem2;
            }
        }
    }
    for(int a = 0; a < taille-1; a++)
    {
        for(int b = 0; b < taille; b++) printf("%5d ", liste[a][b]);
        printf("\n");
    }
    //afficheGraphe(liste,taille);
    for (int v =0; v < taille;v++)
    {
        tableau[v]= liste[tableau4[0]][v];
    }
    printf("km apres heuristique dechange = %d\n",tableau3[0]);
}

void tabou(Graphe g,int *tableau , int taille)
{
    /*
    heuristiqueDechangeDeDeuxSommetsPPVTabou(g,tableau,taille);
    affiche(tableau,taille);
    heuristiqueDechangeDeDeuxSommetsPPVTabou(g,tableau,taille);
    affiche(tableau,taille);
    heuristiqueDechangeDeDeuxSommetsPPVTabou(g,tableau,taille);
    affiche(tableau,taille);
    heuristiqueDechangeDeDeuxSommetsPPVTabou(g,tableau,taille);
    affiche(tableau,taille);
    heuristiqueDechangeDeDeuxSommetsPPVTabou(g,tableau,taille);
    affiche(tableau,taille);
    heuristiqueDechangeDeDeuxSommetsPPVTabou(g,tableau,taille);
    affiche(tableau,taille);
    heuristiqueDechangeDeDeuxSommetsPPVTabou(g,tableau,taille);
    affiche(tableau,taille);
    heuristiqueDechangeDeDeuxSommetsPPVTabou(g,tableau,taille);
    affiche(tableau,taille);
    heuristiqueDechangeDeDeuxSommetsPPVTabou(g,tableau,taille);
    affiche(tableau,taille);
    */
    for (int i = 0; i < taille; i++)
    {
        heuristiqueDechangeDeDeuxSommetsPPVTabou(g,tableau,taille);
        affiche(tableau,taille);
    }
}


int lire_data(char * nom, Graphe * g, int *n, int *m)
{
    char str[15];
    int i, s1, s2, km;
    FILE * f = fopen(nom, "r");

    if (f == NULL) return 0; // le fichier n'existe pas

    // la première ligne contient le nombre de sommets n et le nombre d'arêtes m
    fgets(str, 15, f);
    sscanf(str, "%d %d", n, m);

    // allocation dynamique d'un tableau n x n rempli de 0
    *g = (int **)calloc(sizeof(int *), *n);
    for (i = 0; i < *n; i++) (*g)[i] = (int *)calloc(sizeof(int), *n);

    // lecture du fichier et remplissage du tableau G
    for (i = 0; i < *m; i++)
    {
        fgets(str, 15, f);
        sscanf(str, "%d %d %d", &s1, &s2, &km);
        (*g)[s1][s2] = km;
        (*g)[s2][s1] = km;
    }
    fclose(f);
    return 1;
}

int rnd(int a, int b)
{
    return a + rand() % (b + 1 - a);
}

void permut(int * t, int taille)
{
    int i, j, yam;
    for(i = 0; i < taille-1; i++)
    {
        j = rnd(i, taille-1);
        yam = t[i];
        t[i] = t[j];
        t[j] = yam;
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------

/*
void recupereNumeroDeSommetsTries(Graphe g, int **tab, int taille)
{
    for (int d = 0; d < taille; d++)
    {
        for (int e = 0; e < taille; e++)
        {
            for (int ab = 0; ab < taille; ab++)
            {
                if (tab[d][e]==g[d][ab])
                {
                    tab[d][e] = ab;
                    ab = taille;
                }
            }
        }
    }
}

void recupereNumeroDeSommetsTries(Graphe g, int **tab, int taille)
{
    afficheLigneGraphe(tab,taille,0);
    printf("\n\n");
    afficheLigneGraphe(g,taille,0);
    printf("\n\n");
    for (int d = 0; d < taille; d++)
    {
        // POUR CHAQUE I
        for (int e = 0; e < taille; e++)
        {
            // POUR CHAQUE J
            for (int ab = 0; ab < taille; ab++)
            {
                                            // POUR CHAQUE K
                int yenAcb = 0;
                if (tab[d][e]==g[d][ab])    // SI TAB[I][J] = à GRAPHE[I][K]
                {
                    int i;
                    for (i = 0; i < taille; i++)
                    {
                        if (ab == tab[d][i])
                        {
                            yenAcb++;
                        }

                    }
                    int historique = 0;
                    if (yenAcb > 0)
                    {
                        //printf("mdrr = %d\n",mdr);
                        historique = yenAcb;
                        //ab++; //ici
                        if(yenAcb==2)
                        {
                            tab[d][e] = ab;
                        }
                    }
                    else
                    {
                        //printf("on rentre quand meme dans le else\n");
                        tab[d][e] = ab;
                        ab = taille;
                    }
                }

            }
        }
    }
    afficheLigneGraphe(tab,taille,0);
    printf("\n\n");
    afficheLigneGraphe(g,taille,0);
}


int heuristique_PPV_optimise(Graphe G, int *tableau , int taille, int noSommetDepart)
{
    initialiseTableau(tableau,taille,-1);
    int sommet = trouverSommetLePlusProche(G,noSommetDepart,tableau,taille);
    printf("pour le sommet %d le plus proche est %d \n",noSommetDepart,sommet);
}

int trouverSommetLePlusProche(Graphe g,int numeroSommet, int *listeVisite, int taille)
{
    int memoire, k, j;
    int emplacementDuSommetLePlusProche = 0;
    int i = numeroSommet;
    for (j = 0; j < taille; j++)
    {
        printf("\n\n");
        for (k = j+1; k < taille; k++)
        {
            if (g[i][j]>g[i][k] && g[i][j] != 0)
            {
                memoire = g[i][j];
                g[i][j] = g[i][k];
                if (j==0) emplacementDuSommetLePlusProche = k;
                g[i][k] = memoire;
                printf("%d\n",emplacementDuSommetLePlusProche);
            }
        }

    }
    return emplacementDuSommetLePlusProche;
}


void genererListeParBruteForce(int *tab, int taille, int sommetDeDepart, Graphe g)
{
    int n = 0, i, j, k, p;
    int compteur = 0;
    int valeur = 0;
    int taille2 = taille;
    int memoire;
    affiche(tab,taille);

    addInvisitedList(tab,sommetDeDepart,taille);

    affiche(tab,taille);

    for (int n = 0; n < taille*taille; n++)
    {

        if(compteur > 0)
        {

            initialiseTabAPartirDe(tab,taille,-1,compteur);

            tab[taille-1] = (memoire - 1);

            for (p = 0 ; p < taille; p++)
            {

                if( verifSiDejaVisite(tab,p,taille) == 0 )
                {

                    addInvisitedList(tab,p,taille);

                }

            }

        }
        else
        {
            printf("compteur = %d\n",compteur);
            genererSuiteListe(tab,0,taille);

        }

        affiche(tab,taille);


        compteur++;
        memoire = tab[taille2-1];
    }


}

void genererSuiteListe(int *tab, int valeur, int taille)
{
    for (int j = valeur; j < taille; j++)
    {
        if(verifSiDejaVisite(tab,j,taille)==0) addInvisitedList(tab,j,taille);
    }
}

void BruteForce(int *tab, int taille, int sommetDeDepart, Graphe g)
{
    int i,j;

    for (j = 0; j < taille; j++)
    {
        tab[0]=0;
        if (j==0)
        {
            j++;
        }
        tab[1]=j;

        for (i = 0; i < taille; i++)
        {
            if(verifSiDejaVisite(tab,i,taille)==0)
            {
                addInvisitedList(tab,i,taille);
            }
        }
        affiche(tab,taille);

        initialiseTableau(tab,taille,-1);
    }

}

void forceBrute(int *tab, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        addInvisitedList(tab,i,taille);
        for (int j = i+1; j < taille-1; j++)
        {
            addInvisitedList(tab,j,taille);
            for (int k = j+1; k < taille-2; k++)
            {
                addInvisitedList(tab,k,taille);
                for (int l = k+1; l < taille-3; l++)
                {
                    addInvisitedList(tab,l,taille);
                    for (int m = l+1; m < taille-4; m++)
                    {
                        addInvisitedList(tab,m,taille);
                        for (int n = m+1; n < taille-5; n++)
                        {
                            addInvisitedList(tab,n,taille);
                            for (int o = n+1; o < taille-6; o++)
                            {
                                addInvisitedList(tab,o,taille);
                                for (int p = o+1; p < taille-7; p++)
                                {
                                    addInvisitedList(tab,p,taille);
                                    for (int q = p+1; q < taille-8; q++)
                                    {
                                        addInvisitedList(tab,q,taille);
                                        for (int r = q+1; r < taille-9; r++)
                                        {
                                            addInvisitedList(tab,r,taille);
                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }
        affiche(tab,taille);

    }

}

void initialiseTabDansLordreCroissant(int *tab, int taille)
{
    for (int abi = 0; abi < taille; abi++)
    {
        tab[abi]=abi;
    }
}

void initialiseTabAPartirDe(int *tab, int taille, int valeur, int aPartirDe)
{
    for (int i = aPartirDe; i < taille; i++)
    {
        tab[i]=valeur;
    }
}



void afficheLigneGraphe(Graphe g, int n, int no)
{
    int i, j;
    for(i = no; i < n; i++)
    {
        for(j = 0; j < n; j++) printf("g[%d][%d] = %5d ",i,j,g[i][j]);
        printf("\n");
        i = n;
    }
}

void afficheTabAvecMessage(int * t, int taille, char *msg)
{
    printf("%s\n",msg);
    printf("\n\n");
    for(int i = 0; i < taille; i++) printf("%d\n", t[i]);
    printf("\n\n");
}

*/