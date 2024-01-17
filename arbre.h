#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct noeud;
struct liste_noeud;

struct noeud{
    bool est_dossier;
    char nom [100];
    struct noeud *pere;
    struct noeud *racine;
    struct liste_noeud *fils;
};
struct liste_noeud{
struct noeud *no;
struct liste_noeud *succ;
};
typedef struct noeud noeud;
typedef struct liste_noeud liste_noeud;

/************** Fonction aux **************/
noeud* creer_noeud(char *no,bool ok,noeud* pere,noeud* racine);
noeud* ajout_noeud(char *nom,noeud *courant,noeud* ajout);


/************** Fonction 1 **************/
void ls(noeud* courant);

/************** Fonction 2 **************/
noeud* cd(noeud* courant,char chemin[]);
noeud* cd_racine(noeud* courant);
noeud* cd_parent(noeud* courant);
noeud* chemin_fichier(noeud* courant,char chemin[]);

/************** Fonction 3 **************/
char* pwd(noeud* courant);

/************** Fonction 4 **************/
noeud* mkdir(char *nom,noeud *courant,noeud* rac);

/************** Fonction 5 **************/
noeud* touch(char *nom,noeud *courant,noeud* rac);

/************** Fonction 6 **************/
// La fonction rm marche que quand le chemin n'a pas de fils 
void rm(noeud* courant,char* chemin);
int emplacement_noeud(noeud* courant, noeud * supprime);
void supprime_dossier(noeud* courant, noeud* supprime) ;
void supprime_fichier(noeud* courant, noeud* supprime) ;
void supprime_debut(noeud* courant);
void supprime_fin(noeud* courant);
void supprime_milieu(noeud * courant,noeud *supprime);

/************** Fonction 7 **************/
noeud* premier_noeud(noeud* courant,char chemin[]);
void cp(noeud* courant,char *chem1,char*chem2);

/************** Fonction 8 **************/
void mv(noeud* courant,char *chem1, char*chem2);

/************** Fonction 7 **************/
void affiche_sous_fils(noeud* courant, int niveau_pere);
int nb_noeud(noeud* courant);
void print(noeud *courant);
