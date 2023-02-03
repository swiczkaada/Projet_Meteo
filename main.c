#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


int main(int argc, char *argv[]){
    // argc = nombre d'arguments
    // argv = valeurs des arguments
    // char = caractère ; char * = chaîne de caractère ; char ** = tableau de chaînes de caractères
    // **argv= *argv[]

    struct donnee_meteo *stat = malloc(sizeof(struct donnee_meteo));
        if (stat == NULL) {
            printf("Erreur allocation mémoire.");
            exit(1);
        }
        struct date *date = malloc(sizeof(struct date));
        if (date == NULL) {
            printf("Erreur allocation mémoire.");
            free(stat);
            exit(1);
        }

    if(strcmp (argv[1],"t1") == 0){
        
        int h;
        float donnee2,donnee3;
        PArbre a = NULL;
        FILE* fp=NULL;
        fp=fopen("t1.csv","r");
        if(fp==NULL){
            printf("Erreur ouverture fichier.");
            exit(1); 
        }

        if(strcmp (argv[2],"tab") == 0){
           printf("arg t1 tab");
        }
        else if(strcmp (argv[1],"ABR") == 0){
            printf("arg t1 ABR");
        }
        else{
            while(fscanf(fp, "%f;%d-%d-%dT%d:%*d:%*d%*[+-]%*d:%*d;%f;%f;%f",
                        &(stat->id_station),&(date->year), &(date->month), &(date->day),
                        &(date->hour),&(stat->temperature), &(stat->min),&(stat->max)) != EOF){
                        a=insertionAVL(a,(stat->id_station),(stat->temperature),donnee2,donnee3,(stat->min),(stat->max),&h);
            }
            parcoursInfixe_fichier_t1(a);

            free(stat);
            free(date);
            fclose(fp);
        }
    }
    else if(strcmp (argv[1],"t2") == 0){
        if(strcmp (argv[2],"tab") == 0){
            printf("arg t2 tab");
        }
        else if(strcmp (argv[1],"ABR") == 0){
            printf("arg t2 ABR");
        }
        else{
            printf("arg t2 AVL");
        }
    }
    else if(strcmp (argv[1],"t3") == 0){
        if(strcmp (argv[2],"AVL") == 0){
            printf("arg t3 AVL");
        }
        else if(strcmp (argv[1],"ABR") == 0){
            printf("arg t3 ABR");
        }
        else{
            printf("arg t3 tab");
        }
    }
    else if(strcmp (argv[1],"p1") == 0){

            int h;
            PArbre a = NULL;
            FILE* fp=NULL;
            fp=fopen("p1.csv","r");
            if(fp==NULL){
                printf("Erreur ouverture fichier.");
                exit(1); 
            }

        if(strcmp (argv[2],"tab") == 0){
            printf("arg p1 tab");
        }
        else if(strcmp (argv[1],"ABR") == 0){
            printf("arg p1 ABR");
        }
        else{
            
            while(fscanf(fp, "%f;%f;%f;%f",&(stat->id_station),&(stat->pression_mer), &(stat->pression), &(stat->var_press)) != EOF){
                a=insertionAVL_P1(a,(stat->id_station),(stat->pression_mer),(stat->pression),(stat->var_press),(stat->min),(stat->max),&h);
            }
            parcoursInfixe_fichier_p1(a);
   
            free(stat);
            fclose(fp);
        }
    }
    else if(strcmp (argv[1],"p2") == 0){
        if(strcmp (argv[2],"AVL") == 0){
            printf("arg p2 AVL");
        }
        else if(strcmp (argv[1],"ABR") == 0){
            printf("arg p2 ABR");
        }
        else{
            printf("arg p2 tab");
        }
    }
    else if(strcmp (argv[1],"p3") == 0){
        if(strcmp (argv[2],"AVL") == 0){
            printf("arg p3 AVL");
        }
        else if(strcmp (argv[1],"ABR") == 0){
            printf("arg p3 ABR");
        }
        else{
            printf("arg p3 tab");
        }
    }
    else if(strcmp (argv[1],"w") == 0){
            int h;
            float donnee3;
            PArbre a = NULL;
            FILE* fp=NULL;
            fp=fopen("vent.csv","r");
            if(fp==NULL){
                printf("Erreur ouverture fichier.");
                exit(1); 
            }
        if(strcmp (argv[2],"tab") == 0){
            printf("arg w AVL");
        }
        else if(strcmp (argv[1],"ABR") == 0){
            printf("arg w ABR");
        }
        else{
            
            while(fscanf(fp, "%f;%f;%f",&(stat->id_station),&(stat->O_vent), &(stat->V_vent)) != EOF){
                a=insertionAVL(a,(stat->id_station),(stat->O_vent),(stat->V_vent),donnee3,(stat->min),(stat->max),&h);
            }
            parcoursInfixe_fichier_w(a);
   
            free(stat);
            fclose(fp);
        }
    }
    else if(strcmp (argv[1],"m") == 0){ 
            int h;
            float donnee2,donnee3;
            PArbre a = NULL;
            FILE* fp=NULL;
            fp=fopen("humidite.csv","r");
            if(fp==NULL){
                printf("Erreur ouverture fichier.");
                exit(1); 
            }
        if(strcmp (argv[2],"tab") == 0){
            printf("arg m tab");
        }
        else if(strcmp (argv[1],"ABR") == 0){
            printf("arg m ABR");
        }
        else{
           
            float min,max;
            while(fscanf(fp, "%f;%f",&(stat->id_station),&(stat->humidite)) != EOF){
                a=insertionAVL(a,(stat->id_station),(stat->humidite),donnee2,donnee3,min,max,&h);
             }
            parcoursD_temp(a);
   
            free(stat);
            fclose(fp);
    
        }
    }
    else if(strcmp (argv[1],"h") == 0){

        int h;
        float donnee2,donnee3;
        PArbre a = NULL;
        FILE* fp=NULL;
        fp=fopen("altitude.csv","r");
        if(fp==NULL){
            printf("Erreur ouverture fichier.");
            exit(1); 
        }

        if(strcmp (argv[2],"tab") == 0){
            printf("arg h tab");
        }
        else if(strcmp (argv[1],"ABR") == 0){
            printf("arg h ABR");
        }
        else{
            
            float min,max;
            while(fscanf(fp, "%f;%f",&(stat->id_station),&(stat->altitude)) != EOF){
                a=insertionAVL(a,(stat->altitude),(stat->id_station),donnee2,donnee3,min,max,&h);
            }
            parcoursD_fichier_h(a);
   
            free(stat);
            fclose(fp);
        }
    }
    else{
        printf("Aucune donnée en argument!");
    }

}
