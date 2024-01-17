#include"arbre.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <ctype.h>
#include<assert.h>


/************** Fonction aux **************/
noeud* creer_noeud(char *no,bool ok,noeud* pere,noeud* racine){
    noeud* res=(noeud*)malloc(sizeof(noeud));
    assert(res);
    assert(no);
    res->est_dossier=ok;
    strcpy(res->nom,no);
    res->fils=NULL;
    res->pere=pere;
    res->racine=racine;
    return res;
}

noeud* ajout_noeud(char* nom, noeud* courant, noeud* ajout) {

       liste_noeud* nouveau_fils = malloc(sizeof(liste_noeud));
        assert(nouveau_fils);
        nouveau_fils->no = ajout;
        nouveau_fils->succ = NULL;
        if(courant->fils==NULL){
        courant->fils = nouveau_fils;       
        }
        else 
        {
            liste_noeud *fils_courant=courant->fils;
            while(fils_courant->succ != NULL) {

                if(strcmp(nom,fils_courant->no->nom)==0){
                    puts("erreur vous avez déjà un fils qui porte le même nom !\n\n");     
                    return NULL;
                }
                fils_courant = fils_courant->succ;
            }
            fils_courant->succ=nouveau_fils;
        }
        return ajout;
    }

/************** Fonction 1 **************/
void ls(noeud* courant){
    assert(courant->est_dossier);
    liste_noeud* fils = courant->fils;
    if(fils==NULL){
        puts("pas de fils!");
    }
    while(fils != NULL){
       printf(" %s\n", fils->no->nom);
       fils = fils->succ;
   }
   puts("\n");

}


/************** Fonction 2 **************/
noeud* cd_racine(noeud* courant){
    if(courant->racine->nom==courant->nom) {
        puts("vous etes la racine !");
        return courant->racine;
    }
    return courant->racine;
}

noeud* cd_parent(noeud* courant){
    if(courant->pere->nom==courant->nom) {
        puts("vous etes la racine !");
        return courant->racine;
    }
    return courant->pere;
}

noeud* cd(noeud* courant,char chemin[]){
    if(strcmp(chemin, "")==0 || strcmp(chemin,".")==0) {
        return cd_racine(courant);
    }
    else if(strcmp(chemin,"..")==0){
        return cd_parent(courant);
    }
    else 
    {
        const char* separators="/";
        char* str = malloc(strlen(chemin) + 1); 
        strcpy(str, chemin);
        char* strToken=strtok(str,separators);
        noeud* tmp=courant;
        while(strToken!=NULL){
            liste_noeud* fils=tmp->fils;
            bool ok=false;
            if(fils==NULL){
                return NULL;
            }
            while(fils!=NULL){
                if(strcmp(fils->no->nom,strToken)==0 && fils->no->est_dossier){
                    ok=true;
                    tmp=fils->no;
                    //printf("vous etes dans le dossier'%s'\n\n",fils->no->nom);
                    break;
                }
                fils=fils->succ;
            }
            if(!ok){
                printf("Erreur le chemin n'est pas valide\n\n");
                return NULL;
            }
            strToken=strtok(NULL,separators);
        }
        return tmp;
    }
    
    return NULL;
}

noeud* chemin_fichier(noeud* courant,char chemin[]){
    const char* separators="/ ";
    char* str = malloc(strlen(chemin) + 1); 
    strcpy(str, chemin);
    char* strToken=strtok(str,separators);
    noeud* tmp=courant;
    while(strToken!=NULL){
        liste_noeud* fils=tmp->fils;
        bool ok=false;
        if(fils==NULL){
            return NULL;
        }
        while(fils!=NULL){
            if(strcmp(fils->no->nom,strToken)==0){
                ok=true;
                tmp=fils->no;
                break;
            }
            fils=fils->succ;
        }
        if(!ok){
            printf("Erreur le chemin n'est pas valide\n\n");
            return NULL;
        }
        strToken=strtok(NULL,separators);
    }
    if(tmp->est_dossier==false){ 
        printf("vous etes dans le fichier'%s'\n\n",tmp->nom);
        return tmp;
    }
    return NULL;
}



/************** Fonction 3 **************/
char* pwd(noeud* courant){
    char* res=malloc(sizeof(char));
    assert(res);
    res[0]='\0';
    if(courant==NULL){
        return "Erreur le neoud courant est NULL";
    }
    noeud *rac=courant->racine;
    strcat(res,rac->nom);
    strcat(res,"/");
    char **pere =malloc(10*sizeof(char*));
    assert(pere);
    noeud *p=courant->pere;
    //printf("p: %s\n",p->nom);
    int i=0;
    while(p!=rac){
        pere[i] = malloc(strlen(p->nom) + 1);
        strcpy(pere[i],p->nom);
        strcat(pere[i],"\0");
        //printf("pere[%d]:%s\n",i,pere[i]);
        p=p->pere;
        i+=1;
    }
    //printf("pere[%d]:%s\n",i,pere[i]);
    for(int j=i-1;j>=0;j--){
       // puts("okk");
        strcat(res,pere[j]);
        strcat(res,"/");
    }
    strcat(res,courant->nom);
    return res;
}

/************** Fonction 4 **************/
noeud* mkdir(char *nom,noeud *courant,noeud* rac){
    assert(strlen(nom)<99);
    for (unsigned int i = 0; i < strlen(nom); i++) {
        if (!isalnum(nom[i])) {
            printf("erreur nom ne doit contenir que des caractères alpha-numériques !\n\n");
            return NULL;
        }
    }
    noeud *nouveau=creer_noeud(nom,true,courant,rac);
    if(courant==NULL){
        nouveau->pere=nouveau;
        nouveau->racine=nouveau;
        nouveau->fils=NULL;
        return nouveau;
    } 
    return ajout_noeud(nom,courant,nouveau);
        
}

/************** Fonction 5 **************/
noeud* touch(char *nom,noeud *courant,noeud* rac){
    noeud *nouveau=creer_noeud(nom,false,courant,rac);
    if(courant==NULL){
        nouveau->pere=nouveau;
        nouveau->fils=NULL;
        nouveau->racine=nouveau;
        return nouveau;
    } 
       
   return ajout_noeud(nom,courant,nouveau);
}

/************** Fonction 6 **************/
// La fonction rm marche que quand le chemin n'a pas de fils 
void rm(noeud* courant,char* chemin){
    noeud *supprime_d=cd(courant,chemin);
    noeud *supprime_f=chemin_fichier(courant,chemin);
    if(supprime_d!=NULL && supprime_f==NULL){
         if(supprime_d==courant->pere){
        puts("Erreur vous ne pouvez pas supprimer le noeud parent du noeud où se trouve le programme\n\n");
        return;
    }
       supprime_dossier(courant,supprime_d);
    } 
    else if(supprime_d==NULL && supprime_f!=NULL){
        supprime_fichier(courant,supprime_f);
    }
    else
    {
        puts("Erreur le chemin n'existe pas\n\n");
        return;
    }
   
}

int emplacement_noeud(noeud* courant, noeud * supprime){ 
    int res=-4;
    if (courant != NULL) {
        if(supprime->nom==courant->fils->no->nom){
                res=0;
        } else { 
            liste_noeud* fils_pere = courant->fils;
            for (;fils_pere != NULL;fils_pere=fils_pere->succ) {
                if(supprime==fils_pere->no){
                    if(fils_pere->succ==NULL){
                        res=-1;
                    } else { 
                        res=1;
                    }
                }
            }
        }
    }
    return res;
}

void supprime_debut(noeud* courant){
    assert(courant);
    puts("premier\n");
    liste_noeud* fils_pere = courant->fils;
    courant->fils=courant->fils->succ;
    free(fils_pere->no);
    free(fils_pere);
    puts("suppression réussi\n\n");
}

void supprime_fin(noeud* courant){
    puts("dernier\n");
    liste_noeud* fils_pere = courant->fils;
    while (fils_pere->succ->succ != NULL) {
        fils_pere=fils_pere->succ;
            
    }
    free(fils_pere->succ->no); 
    free(fils_pere->succ);
    fils_pere->succ=NULL;
    puts("suppression réussi\n\n");
}

void supprime_milieu(noeud * courant,noeud *supprime){
    puts("milieu\n\n");
    liste_noeud* fils_pere = courant->fils;
    for (;fils_pere != NULL;fils_pere=fils_pere->succ) {
                
    if (fils_pere->no == supprime) {

        liste_noeud* tmp=fils_pere;
    
        fils_pere=fils_pere->succ;
        courant->fils->succ = fils_pere;

        free(tmp->no);     
        free(tmp);
                    
        puts("suppression réussi\n\n");
        break;
        }
    }
}

void supprime_fichier(noeud* courant, noeud* supprime) {
    printf("noeud a supprimer : %s\n\n",supprime->nom);
    if (courant != NULL) {
        if(emplacement_noeud(courant,supprime)==1){ 
            supprime_milieu(courant,supprime);
        }
        else if(emplacement_noeud(courant,supprime)==-1){
            supprime_fin(courant);
            }
            else if(emplacement_noeud(courant,supprime)==0) {
                supprime_debut(courant);
            }
            return;
        }
    
    free(supprime);
}


void supprime_dossier(noeud* courant, noeud* supprime) {
    // on supprime les fils du noeud courant
    liste_noeud* fils = supprime->fils;
    while (fils != NULL) {
        liste_noeud* tmp = fils;
        supprime_dossier(courant,fils->no);
        fils = fils->succ;
        free(tmp);
    }
    supprime->fils=NULL;
    // on supprime le fils du noeud parent contenant le noeud courant
    noeud* p=supprime->pere;
    courant=p;
    if (courant != NULL) {
        if(emplacement_noeud(courant,supprime)==1){ 
            supprime_milieu(courant,supprime);
        }
        else if(emplacement_noeud(courant,supprime)==-1){
            supprime_fin(courant);
            }
            else if(emplacement_noeud(courant,supprime)==0) {
                supprime_debut(courant);
            }
            return;
        }
    free(supprime);             
}




/************** Fonction 7 **************/
noeud* premier_noeud(noeud* courant,char chemin[]){
        const char* separators="/ ";
        char* str = malloc(strlen(chemin) + 1); 
        strcpy(str, chemin);
        char* strToken=strtok(str,separators);
        //noeud* tmp=courant;
        liste_noeud* fils=courant->fils;
        while(strToken!=NULL){ 
            while(fils!=NULL){
                if(strcmp(strToken,fils->no->nom)==0){
                    return fils->no;
                }
                fils=fils->succ;
            }
        }
        return NULL;
}

void cp(noeud* courant,char *chem1,char*chem2){
    noeud* n1=cd(courant,chem1);
    noeud* n1_bis=chemin_fichier(courant,chem1);
    noeud* n2=cd(courant,chem2);

    if(n1==NULL && n1_bis==NULL){
        puts("Erreur il n’y a pas de noeud au chemin d’adresse chem1\n\n");
        return;
    }
    if(n2==NULL || n2->est_dossier==false){
        puts("Erreur chem2 n'est pas un dossier\n\n");
        return;
    }
    if(n2->fils==NULL){ 
        noeud *test=premier_noeud(courant,chem2);
        if(strcmp(test->nom,n1->nom)==0){
            puts("Erreur le dossier chem2 a un fils ayant pour nom le dernier nom du chemin du noeud indiqué par chem2 \n\n");
            return;
        }
        liste_noeud *noeud_chem2=premier_noeud(courant,chem2)->fils;
        //printf("noeud %s\n\n",noeud_chem2->no->nom);
        for(;noeud_chem2!=NULL;noeud_chem2=noeud_chem2->succ){
            if(strcmp(noeud_chem2->no->nom,n1->nom)==0){
                puts("Erreur le dossier chem2 a un fils ayant pour nom le dernier nom du chemin du noeud indiqué par chem2 \n\n");
                return;
            }
        }
        if(n1==NULL && n1_bis!=NULL){
            //puts("fichier\n\n");
            touch(n1_bis->nom,n2,n2->racine);
            return;
        }
        else if(n1!=NULL && n1_bis==NULL){
            noeud* copie=(noeud*) malloc(sizeof(noeud));
            noeud* p=n2->pere;
            noeud* rac=n2->racine;

            memmove(copie,n1,sizeof(noeud));
            //printf("copie : %s\n\n",copie->nom);
            strcpy(copie->nom,n2->nom);
            memmove(n2,copie,sizeof(noeud));
            n2->pere=p;
            n2->racine=rac;
            liste_noeud *f=n2->fils;
            for(;f!=NULL;f=f->succ){
                f->no->pere=n2;
            }
            return;
        }
    }
}

/************** Fonction 8 **************/
void mv(noeud* courant,char *chem1, char*chem2){
    noeud *n1=cd(courant,chem1);
    noeud *n2=cd(courant,chem2);
    if(n1==NULL || n2==NULL){
        puts("Erreur chemin non valide\n\n");
        return;
    }
    if(n2!=NULL && n2->est_dossier==true && n2->fils==NULL){ 
        noeud *test=premier_noeud(courant,chem2);
        if(strcmp(test->nom,n1->nom)==0){
            puts("Erreur le dossier chem2 a un fils ayant pour nom le dernier nom du chemin du noeud indiqué par chem2 \n\n");
            return;
        }
        liste_noeud *noeud_chem1=premier_noeud(courant,chem2)->fils;
        printf("noeud %s\n\n",noeud_chem1->no->nom);
        for(;noeud_chem1!=NULL;noeud_chem1=noeud_chem1->succ){
            if(strcmp(noeud_chem1->no->nom,n2->nom)==0){
                puts("Erreur le dossier chem2 a un fils ayant pour nom le dernier nom du chemin du noeud indiqué par chem2 \n\n");
                return;
            }
        }
    cp(courant,chem1,chem2);
    rm(courant,chem1);
    }
}

/************** Fonction 9 **************/
int nb_noeud(noeud* courant){
    int res=0;
    if(courant->fils==NULL){
        res=0;
    }
    for(liste_noeud* fils=courant->fils;fils!=NULL;fils=fils->succ){
        res++;
    }
    return res;
}

void affiche_sous_fils(noeud* courant, int niveau_pere) {
    assert(courant);

    liste_noeud* fils_courant = courant->fils;
    //printf("\n");
    while (fils_courant != NULL) {
        for (int i = 0; i < niveau_pere; i++) {
            printf("=");
        }
        printf(" ");
        char ok=(fils_courant->no->est_dossier==true) ? 'D' : 'F';
        printf("niveau %d (%c) %s : %d fils\n", niveau_pere, ok, fils_courant->no->nom, nb_noeud(fils_courant->no));

        if (fils_courant->no->fils != NULL) {
            affiche_sous_fils(fils_courant->no, niveau_pere + 1);
        }

        fils_courant = fils_courant->succ;
    }
}

void print(noeud *courant){
    assert(courant);
    printf("noeud courant : '%s' %d fils \n",courant->nom,nb_noeud(courant));
    if(courant->est_dossier==false || courant->fils==NULL){
        return;
    } else {
        liste_noeud * fils_courant=courant->fils;
        int cpt=0;
        while(fils_courant!=NULL){
            char ok=(fils_courant->no->est_dossier==true) ? 'D' : 'F';
            if(fils_courant->no->fils==NULL){
                printf("fils %d : %s (%c) %d fils \n",cpt,fils_courant->no->nom,ok,nb_noeud(fils_courant->no));
            } else { 
                printf("fils %d : %s (%c) %d fils-> :  \n",cpt,fils_courant->no->nom,ok,nb_noeud(fils_courant->no));
            }

            affiche_sous_fils(fils_courant->no,cpt+1);
            
            cpt++;
            fils_courant=fils_courant->succ;
        }
    }
}