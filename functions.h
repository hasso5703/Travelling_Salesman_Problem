#ifndef tsp_h
#define tsp_h

typedef int ** Graphe;

int     heuristiqueDuPlusProcheVoisin               (Graphe G, int **tab2dim, int **tab2dim2, int *tableau , int taille, int noSommetDepart);
void    heuristiqueAleatoire                        (Graphe g, int *tab, int taille);
int     lire_data                                   (char *nom, Graphe *, int *n, int *m);
int     rnd                                         (int, int);
int     genereNombreAleatoire                       (int nbMax);
int     calculerKmParcouru                          (Graphe, int *tableau, int taille);
int     verifSiDejaVisite                           (int *tab,int nombre,int taille);
void    heuristiqueAleatoireParPermutation          (Graphe G,int *tabAPermut, int taille);
void    verifSiDejaVisiteEtAjoutDansListe           (int *tab,int nombre,int taille);
void    permut                                      (int *, int);
void    affiche                                     (int *, int);
void    trieGraphe                                  (int **,int **, int);
void    addInvisitedList                            (int *tab, int,  int);
void    genererListeAleatoire                       (int, int *);
void    faireUneCopieDuGraphe                       (Graphe g, int **tab, int taille);
void    initialiseTableau                           (int *tab, int taille, int valeur);
void    genererListePlusProcheVoisin                (int **tab2dim ,int *tab, int taille);
void    initialiseGrapheAvecSommets                 (int **tab, int taille);
void    heuristiqueDechangeDeDeuxSommetsPPV         (Graphe g, int *tableau , int taille);
void    essayerTousLesSommetsDeDepartsPourPPV       (Graphe G, int **tab2dim, int **tab2dim2, int *tableau , int taille);
void    heuristiqueDeDecroismentDeDeuxArretes       (Graphe g, int *tab, int taille);
void    heuristiqueDechangeDeDeuxSommetsPPVTabou    (Graphe g,int *tableau , int taille);
void    tabou                                       (Graphe g,int *tableau , int taille);

#endif

/*
void    afficheGraphe                           (Graphe, int taille);
void    afficheTab2Dim                          (int **tab, int taille);
void    ajouteTable                             (int *tab, int nb, int taille);
void    genererListeParBruteForce               (int *tab, int taille, int sommetDeDepart, Graphe g);
void    initialiseTabDansLordreCroissant        (int *tab, int taille);
int     trouverSommetLePlusProche               (Graphe g,int numeroSommet, int *tab, int taille);
int     heuristique_PPV_optimise                (Graphe G, int *tableau , int taille, int noSommetDepart);
void    genererSuiteListe                       (int *tab, int valeur, int taille);
void    afficheTabAvecMessage                   (int * t, int taille, char *msg);
void    initialiseTabAPartirDe                  (int *tab, int taille, int valeur, int aPartirDe);
void    BruteForce                              (int *tab, int taille, int sommetDeDepart, Graphe g);
void    afficheLigneGraphe                      (Graphe g, int n, int no);
void    forceBrute                              (int *tab, int taille);
void    recupereNumeroDeSommetsTries            (Graphe g, int **tab, int taille);
 */