#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int max2(int a, int b) {
    return (a<b ? b : a);
}
int max3(int a, int b, int c) {
    return max2(max2(a,b),c);
}
int min2(int a, int b) {
    return (a < b ? a : b);
}
int min3(int a, int b, int c) {
    return min2(min2(a,b),c);
}


bool estVide(PArbre a) {
 return (a == ARBRENULL);
}
PArbre filsGauche(PArbre a) {
return a->fg;
}
PArbre filsDroit(PArbre a) {
return a->fd;
}
int hauteur(PArbre a) {
if (estVide(a)) return -1;
return 1 + max2(hauteur(filsGauche(a)), hauteur(filsDroit(a)));
}

PArbre creerAVL(Element e, float donnee1,float donnee2, float donnee3, float min, float max) {
    PArbre a;
    if ((a = MALLOC(Arbre)) == NULL) {
        fprintf(stderr, "ERREUR ALLOCATION MEMOIRE NOEUD %f\n", e);
        exit(1);
    }
    *a = (Arbre) { e,donnee1,donnee2,donnee3,donnee1,donnee2,donnee3,1,donnee1,donnee2,donnee3,min,max, ARBRENULL, ARBRENULL, 0, 0};
    return a;
}

PArbre rotationGauche(PArbre a){
    PArbre pivot;
    int eq_a, eq_p;

    pivot = a->fd;

    a->fd = pivot->fg;
    pivot->fg =a;
    eq_a=a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - max2(eq_p, 0) -1;
    pivot->equilibre = min3(eq_a-2,eq_a+eq_p-2, eq_p-1);
    a=pivot;
    return a;
}

PArbre rotationDroite(PArbre a){
    PArbre pivot;
    int eq_a, eq_p;

    pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd =a;
    eq_a=a->equilibre;
    eq_p = pivot->equilibre;
    a->equilibre = eq_a - min2(eq_p, 0) +1;
    pivot->equilibre = max3(eq_a+2,eq_a+eq_p+2, eq_p+1);
    a=pivot;
    return a;
}

PArbre doubleRotationGauche(PArbre a){
    a->fd = rotationDroite(a->fd);
    return rotationGauche(a);
}

PArbre doubleRotationDroite(PArbre a){
    a->fg = rotationGauche(a->fg);
    return rotationDroite(a);
}

PArbre equilibrageAVL(PArbre a){
    if (a->equilibre >=2){
        if(a->equilibre >=0) return rotationGauche(a);
        else return doubleRotationGauche(a);
    }
    if(a->equilibre <=-2){
        if(a->equilibre <=0) return rotationDroite(a);
        else return doubleRotationDroite(a);
    }
    return a;
}

/* Insertion id_station/temperature + calcule de la moyenne des temperatures pour chaque station */

PArbre insertionAVL(PArbre a, Element e, float donnee1, float donnee2, float donnee3, float min, float max, int *h){ 
    if(!a){
        *h=1;    
        return creerAVL(e,donnee1,donnee2,donnee3,min,max);
        }
    
    if(e < a->elmt){
        a->fg = insertionAVL(a->fg,e,donnee1,donnee2,donnee3,min,max,h);
        *h = -*h;
    }
    else if(e > a->elmt){
        a->fd = insertionAVL(a->fd,e,donnee1,donnee2,donnee3,min,max,h);
    }   
    else{
        a->som1 += donnee1;                               /***************************************/
        a->som2 += donnee2;                              /******moyenne pour t1(moy1) ***********/                                           
        a->nbstation++;                                 /* moyenne pour orientation vent (moy1)*/
        a->moy1 = a->som1 / a->nbstation;              /* moyenne pour direction vent (moy2) */
        a->moy2 = a->som2 / a->nbstation;             /**************************************/
        *h=0;
        return a;
    }
  
    if(*h != 0){
        a->equilibre = a->equilibre + *h;
        a= equilibrageAVL(a);
        if(a->equilibre == 0) *h=0;
        else *h=1;
    }
    return a;
}
/*Insertion AVL pour l'option p1 : donnee1 = Pression au niveau mer, donnee2 = Pression, donnee3 = variation de pression*/
PArbre insertionAVL_P1(PArbre a, Element e, float donnee1, float donnee2, float donnee3, float min, float max, int *h){ 

        //Pression moyenne = (Pression au niveau mer + Pression station + Variation de pression en 24 heures) / 3
        //Pression minimum = Pression station - Variation de pression en 24 heures
        //Pression maximum = Pression station + Variation de pression en 24 heures
        float moyenne = (donnee1 + donnee2 + donnee3)/3;
        float minimum = donnee2 - donnee3;
        float maximum = donnee2 + donnee3;

        if(!a){
          *h=1;
          return creerAVL(e,donnee1,donnee2,moyenne,minimum,maximum);
        }
   
        if(e < a->elmt){
            a->fg = insertionAVL_P1(a->fg,e,donnee1,donnee2,donnee3,min,max,h);
            *h = -*h;
        }
        else if(e > a->elmt){
            a->fd = insertionAVL_P1(a->fd,e,donnee1,donnee2,donnee3,min,max,h);
        }
        
        else{                    
          a->som3 += moyenne;                           
          a->nbstation++;                                   
          a->moy3 = a->som3 / a->nbstation; 

        if(maximum > a->max){
            a->max=maximum;
        }
        if(minimum < a->min){
            a->min=minimum;
        }
           
        *h=0;
        return a;
        }
        if(*h != 0){
            a->equilibre = a->equilibre + *h;
            a= equilibrageAVL(a);
        if(a->equilibre == 0) *h=0;
        else *h=1;
    }
    return a;
}
/*Insertion AVL pour l'option h*/
PArbre insertionAVL_H(PArbre a, Element e, float donnee1,float donnee2,float donnee3, float min, float max, int *h){ 
    if(!a){
        *h=1;    
        return creerAVL(e,donnee1,donnee2,donnee3,min,donnee1);
        }
    
    if(e < a->elmt){
        a->fg = insertionAVL_H(a->fg,e,donnee1,donnee2,donnee3,min,max,h);
        *h = -*h;
        }
    else if(e > a->elmt){
        a->fd = insertionAVL_H(a->fd,e,donnee1,donnee2,donnee3,min,max,h);
    }
        
    else{
        if(donnee1 > a->max){
            a->max=donnee1;
        }              
        *h=0;
        return a;
    }
    if(*h != 0){
        a->equilibre = a->equilibre + *h;
        a= equilibrageAVL(a);
        if(a->equilibre == 0) *h=0;
        else *h=1;
    }
    return a;
}


/*
* Affichage de l'arbre
*/

//affichage donnee t1 dans fichier sortie 
void parcoursInfixe_fichier_t1(PArbre a){  
    FILE* ofp=NULL;
    ofp=fopen("temperaturet1.dat", "w");
        if(ofp == NULL){
            printf("Erreur ouverture fichier.");
        }
    parcoursCroissant_t1(a,ofp);
}

// Affichage ordre croissant des stations + min,max,moyenne(temperature) par station
void parcoursCroissant_t1(PArbre a, FILE* ofp) { 
    if (! estVide(a)) {
    parcoursCroissant_t1(filsGauche(a), ofp);
    fprintf(ofp, "%f %f %f %f \n", a->elmt, a->min, a-> max, a->moy1);
    parcoursCroissant_t1(filsDroit(a), ofp);
    }
}

//affichage de t1 dans fichier sortie 
void parcoursInfixe_fichier_p1(PArbre a){  
    FILE* ofp=NULL;
    ofp=fopen("pression1.dat", "w");
        if(ofp == NULL){
            printf("Erreur ouverture fichier.");
        }
    parcoursCroissant_p1(a,ofp);
}
// Affichage ordre croissant des stations + min,max,moyenne pression par station
void parcoursCroissant_p1(PArbre a, FILE* ofp) { 
    if (! estVide(a)) {
    parcoursCroissant_p1(filsGauche(a), ofp);
    fprintf(ofp, "%0f %f %f %f \n", a->elmt, a->min, a-> max, a->moy3);
    parcoursCroissant_p1(filsDroit(a), ofp);
    }
}

void parcoursInfixe_fichier_w(PArbre a){  
    FILE* ofp=NULL;
    ofp=fopen("vent.dat", "w");
        if(ofp == NULL){
            printf("Erreur ouverture fichier.");
        }
    parcoursCroissant_w(a,ofp);
}
// Affichage ordre croissant des stations + moyenne orientation et direction du vent par station
void parcoursCroissant_w(PArbre a, FILE* ofp) { 
    if (! estVide(a)) {
    parcoursCroissant_w(filsGauche(a), ofp);
    fprintf(ofp, "%f %f %f \n", a->elmt, a->moy1, a-> moy2);
    parcoursCroissant_w(filsDroit(a), ofp);
    }
}
void parcoursD_fichier_h(PArbre a){  
    FILE* ofp=NULL;
    ofp=fopen("meteoalt.dat", "w");
        if(ofp == NULL){
            printf("Erreur ouverture fichier.");
        }
    parcoursD_h(a,ofp);
}
void parcoursD_h(PArbre a, FILE* ofp){
    if (! estVide(a)) {
    parcoursD_h(filsDroit(a),ofp);
    fprintf(ofp,"%f %f\n", a->donnee1, a->elmt);
    parcoursD_h(filsGauche(a),ofp);
    }
}

void parcoursD_fichier_m(PArbre a){  
    FILE* ofp=NULL;
    ofp=fopen("meteohumidite.dat", "w");
        if(ofp == NULL){
            printf("Erreur ouverture fichier.");
        }
    parcoursD_m(a,ofp);
}
void parcoursD_m(PArbre a, FILE* ofp){
    if (! estVide(a)) {
    parcoursD_m(filsDroit(a),ofp);
    fprintf(ofp,"%f %f\n", a->elmt, a->max);
    parcoursD_m(filsGauche(a),ofp);
    }
}

