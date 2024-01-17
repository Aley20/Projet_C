#include "arbre.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <ctype.h>
#include<assert.h>


int main(int argc, char *argv[]) {
    assert(argc==2);

    FILE *fichier;
    char ligne[100];

    fichier = fopen(argv[1], "r");
    
    if (fichier == NULL) {
        printf("Erreur \n");
        return 1;
    }

    noeud * A1=mkdir("",NULL,NULL);
    noeud * courant=A1; 

    while (fgets(ligne, sizeof(ligne), fichier)) {
        ligne[strcspn(ligne, "\n")] = '\0';

        char* token = strtok(ligne, " ");
        char *commande=malloc(sizeof(char));
        char *argument=malloc(sizeof(char));
        char *argument1=malloc(sizeof(char));

        if (token != NULL) {
            strcpy(commande, token); 

            token = strtok(NULL, " "); 
            if (token != NULL) {
                strcpy(argument, token); 
            }
            else 
            {
                strcpy(argument, "");
            }
            token = strtok(NULL, " ");
            if(token!=NULL){
                strcpy(argument1,token);
            }
        }

        if (strcmp(commande, "mkdir") == 0) {
            mkdir(argument, courant, A1 );
            //printf("ajout de %s\n",argument);
        } else if (strcmp(commande, "ls") == 0) {
            puts("--------------------- ls ---------------------\n");
            ls(courant);
            puts("----------------------------------------------\n");
        } else if(strcmp(commande,"cd") == 0){
                //printf("vous etes dans -> [%s] \n",courant->nom);
                courant=cd(courant,argument);
            //printf("vous etes dans -> %s \n",courant->nom);
        } else if(strcmp(commande,"touch") == 0){
            touch(argument,courant,A1);
            printf("ajout de %s\n",argument);
        } else if(strcmp(commande,"pwd") == 0){
            puts("--------------------- pwd ---------------------\n");
            char* c=pwd(courant);
            printf("%s\n",c);
            puts("----------------------------------------------\n");
        } else if(strcmp(commande,"print") == 0){
            puts("--------------------- print ---------------------\n");
            print(A1);
            puts("----------------------------------------------\n");
        } else if(strcmp(commande,"rm")==0){
            rm(courant,argument);
        } else if(strcmp(commande,"cp")==0){
            cp(courant,argument,argument1);
        } else if(strcmp(commande,"mv")==0){
            mv(courant,argument,argument1);
        }
        free(commande);
        free(argument);
    }
    fclose(fichier);

    return 0;
}