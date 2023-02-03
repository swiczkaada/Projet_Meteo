## Projet CY-Météo

(Carla et Adam Swiczka PRE ING2 M15)

Une application utilisée pour filtrer et traiter les données météorologiques en fonction des préférences de l'utilisateur, construite avec Shell et le langage C.
L'affichage de ces données triées permet à l'utilitaire gnluplot de générer des graphiques de type vecteurs, 'carte interpolé' ou de 'barre d'erreur .

## Comment installer et exécuter le projet ?

Instructions de compilation .
1)	Ouvrez l'invite de commande
2)	Déplacez-vous dans le répertoire MET EO
3)	Exécutez la commande "make" pour générer l'éxécutable
4)	Exécutez la commande "make clean" pour supprimer les fichiers objets
5)	Exécuter la commande I ./scriptshell I sans oublier les arguments.

## Comment utiliser le projet?

[TRIS] : -- tab : tri de données à l'aide d'un tableau (ou liste chaînée) -- abr : tri à l'aide d'une structure d'arbre binaire ABR ou AVL -- avl
[LIEUX] : -F : France métropolitaine + Corse.
-G : Guyane française
-S : Saint-Pierre et Miquelon
-A : Antilles
-O : Océan indien
-Q . Antarctique
[TYPE de données] : - p < pressions atmosphériques >
-t <temperatures >
1 : min, max, moy par ID_station croissant 2: moy par dates/heures. Ordre chronologique 3: val par dates/heures.
Ordre chronologique I ordre ID_station croissant
-w < vent > :
-h < attitude >
-m < humidité >
  
## L'état du projet
  
Ce projet est actuellement inachevé.
Les utilisateurs peuvent filtrer les données selon la zone géographiques, les options et les tri.Cependant la fonctionnalité de tri est incomplète, les options p2/t2 et et p3/t3 et le tri -tab n'ont pas été codé .
I l est également impossible de filtrer par la date et certains options peuvent partiellement fonctionner selon les conditions.
## Capture(s) d'écran du projet
 

