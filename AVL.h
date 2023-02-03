#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


#define MALLOC(type) ((type * ) malloc(sizeof(type)))

#define ELEMENTNULL 0
#define ARBRENULL NULL

typedef float Element;

struct date {
    int hour;
    int day;
    int month;
    int year;
    
};

struct donnee_meteo{
    float id_station;
    float temperature;
    float pression_mer; // Pression au niveau mer
    float pression;
    float var_press; // Variation de pression en 24 heures
    float O_vent; // orientation du vent
    float V_vent; // vitesse du vent
    float humidite;
    float altitude;
    float min;
    float max;
    struct date date;
};


typedef struct arb {
    Element elmt;
    float donnee1;
    float donnee2;
    float donnee3;
    float som1;
    float som2;
    float som3;
    int nbstation;
    float moy1;
    float moy2;
    float moy3;
    float min;
    float max;
    struct arb* fg;
    struct arb* fd;
    int equilibre;
    int hauteur;
} Arbre;

typedef Arbre* PArbre;
 

int max2(int a, int b);
int max3(int a, int b, int c);
int min2(int a, int b);
int min3(int a, int b, int c);
bool estVide(PArbre a); 
PArbre filsGauche(PArbre a);
PArbre filsDroit(PArbre a);
int hauteur(PArbre a);

PArbre creerAVL(Element e, float donnee1, float donnee2, float donnee3, float min, float max);
PArbre recherche(PArbre a, Element e);
PArbre rotationGauche(PArbre a);
PArbre rotationDroite(PArbre a);
PArbre doubleRotationGauche(PArbre a);
PArbre doubleRotationDroite(PArbre a);
PArbre equilibrageAVL(PArbre a);
PArbre insertionAVL(PArbre a, Element e, float donnee1, float donnee2, float donnee3, float min,float max, int *h);
PArbre insertionAVL_P1(PArbre a, Element e, float donnee1, float donnee2, float donnee3, float min,float max, int *h);
PArbre insertionAVL_H(PArbre a, Element e, float donnee1, float donnee2, float donnnee3, float min, float max, int *h);

void parcoursInfixe_fichier_t1(PArbre a);
void parcoursCroissant_t1(PArbre a, FILE* ofp);
void parcoursInfixe_fichier_p1(PArbre a);
void parcoursCroissant_p1(PArbre a, FILE* ofp);
void parcoursInfixe_fichier_w(PArbre a);
void parcoursCroissant_w(PArbre a, FILE* ofp);
void parcoursD_fichier_h(PArbre a);
void parcoursD_h(PArbre a,FILE* ofp);
void parcoursD_fichier_m(PArbre a);
void parcoursD_m(PArbre a, FILE* ofp);


#endif
