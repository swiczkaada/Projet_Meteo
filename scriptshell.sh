#!/bin/bash               
w=0                     #declaration de variable
h=0
m=0
d=0
t=0
p=0
count=0
x=0
a=0
while getopts ":-:d:t:p:whmFGQSAO" option; do       #different cas en fonction des options sélectionner
    case "${option}" in
    t) t="$OPTARG" #recupere l argument du t
    ;;
    p) p="$OPTARG" #recupere l argument du p
    ;; 
    w) w=1
    ;;
    h) h=1
    ;;
    m) m=1
    ;;
    F) cat meteo.csv | awk -F";" '{split($10,coo,",");if(coo[2] + 0 >= 5 && coo[2] + 0 <= 10 && coo[1] + 0 <= 52 && coo[1] +0 >= 41) print $0 }' > meteoloca.csv #split les coordonnée en un tableau et compare avec les coordonnée pour ne garder que ceux du pays
    ((count++))  # augmente le compteur d un
    ;;
    G) awk -F";" '$15 ~ /^973/' meteo.csv > meteoloca.csv #Guyane
    ((count++))
    ;; #longitude 2 lattitude 1
    Q) cat meteo.csv | awk -F";" '{split($10,coo,",");if(coo[1] + 0 <= -83 && coo[1] +0 >= -55) print $10 }' > meteoloca.csv
    ((count++)) #Antartique
    ;;
    d) d="$OPTARG"
    ;;
    S) awk -F";" '$15 ~ /^975/' meteo.csv > meteoloca.csv
    ((count++)) #ne garde que les région au département commençant par 975
    ;;
    A) awk -F";" '$15 ~ /^971/' meteo.csv > meteoloca.csv
    ;;
    O) awk -F";" '$15 ~ /^97/' meteo.csv > meteoloca.csv
    ;;
    -) case "${OPTARG}" in #s'occupe des arguments de tris et de help
            help) echo "séléctionner une option. -t1(-p1) indique les temperature(préssion) min,max,moy par station  -t2(-p2) temperature moyenne par date/heure. -t3(p3) temperature(pression) par date heure. -w orientation moyenne et vitesse des veny. -h  altitude classé par ordre moyen -m humidité max. Vous ne pouvez séléctionner qu'une optio de localisation (-F -G -A -O) et nous sommes aux regrets de vous annoncer qu'il n'y à pas d'option date." ;;
            avl | abr ) x="$OPTARG" ;;
            *) echo "argument incorrect"
                exit 1 ;;
            esac
    ;;
    *) echo "option non reconnue" # si aucune option n"est programé quitte le programme
    exit 1
    ;;
    esac
done
if [ $count -gt 1 ] ; then #verifie qu'une seule option de localisation
    echo "vous n'etes autorisé à ne selectionner qu'une contrainte de lieu."
    exit 1
   
elif [ "$t" -lt 0 ] || [ "$t" -gt 3 ]; then #verifie que l option de t est comprise entre 1 et 3
    echo "l'option choisis n'est pas valide"
elif [ "$t" -eq "1" ]; then
    a="t1"
     if [ -e meteoloca.csv ]; then # regarde si il y a un arg localisation
        cut -d ";" -f 1,11,12,13 meteoloca.csv > t1.csv
     else
        cut -d ";" -f 1,11,12,13 meteo.csv > t1.csv #sinon agi directement en fonction du fihier de base
     fi
     sed -i -r 's/;/ 0/g' t1.csv #remplace les ; par des 0
     sed -i 's/ /;/g' t1.csv #remplace les ' ' par des points virgules
     tail -n +2 t1.csv > t1t.csv
     ./main.c "$a" "$x" t1t.csv temperaturet1.dat  # appel le tri en c et indique le type de donné
    gnuplot "t1etp1.p"
elif [ "$t" -eq "2" ]; then
    a="t2"
    if [ -e meteoloca.csv ]; then
        cut -d ";" -f 1,11,12,13 meteoloca.csv > t2.csv
    else
        cut -d ";" -f 1,11,12,13 meteo.csv > t2.csv
    fi
     sed -i -r 's/;/ 0/g' t2.csv #remplace les ; par des 0
     sed -i 's/ /;/g' t2.csv #remplace les ' ' par des points virgules
     tail -n +2 t2.csv > t2t.csv
    ./test "$a" "$x" t2t.csv temperaturet2.dat
    gnuplot "t2etp2.p"
elif (( $t == "3" )); then
    a="t3"
     if [ -e meteoloca.csv ]; then
        cut -d ";" -f 1,11,12,13 meteoloca.csv > t3.csv
    else
        cut -d ";" -f 1,11,12,13 meteo.csv > t3.csv
    fi
     sed -i -r 's/;/ 0/g' t3.csv #remplace les ; par des 0
     sed -i 's/ /;/g' t3.csv #remplace les ' ' par des points virgules
     tail -n +2 t3.csv > t3t.csv
    ./test "$a" "$x" t3t.csv temperaturet3.dat
    cat temperaturet3.dat
fi
if (( $p !=0 && $p < 1 || $p !=0 && $p > 3 )); then #attaque les pressions et verifie que l'argument estvalide
    echo "l'option choisis n'est pas valide"
elif (( $p == 1 )); then
    a="p1"
    if [ -e meteoloca.csv ]; then
        cut -d ";" -f 1,3,7,8 meteoloca.csv > pression.csv
    else
        cut -d ";" -f 1,3,7,8 meteo.csv > pression.csv
    fi
     sed -i -r 's/;/ 0/g' pression.csv
     sed -i 's/ /;/g' pression.csv
     tail -n +2 pression.csv > pressiont.csv
    ./test "$a" "$x" pressiont.csv pression1.dat
    gnuplot "p1.p"
 
elif (( $p == 2 )); then
    a="p2"
    if [ -e meteoloca.csv ]; then
        cut -d ";" -f 1,2,3,7,8 meteoloca.csv > pression2.csv
    else
        cut -d ";" -f 1,2,3,7,8 meteo.csv > pression2.csv
    fi
    sed -i -r 's/;/ 0/g' pression2.csv
    sed -i 's/ /;/g' pression2.csv
    tail -n +2 pression2.csv > pressiont2.csv
    ./test "$a" "$x" pressiont2.csv pression2.dat
    gnuplot "p2.p"
elif [ "$p" -eq "3" ]; then
    a="p3"
    if [ -e meteoloca.csv ]; then
        cut -d ";" -f 1,2,3,7,8 meteoloca.csv > pression3.csv
    else
        cut -d ";" -f 1,2,3,7,8 meteo.csv > pression3.csv
    fi
    sed -i -r 's/;/ 0/g' pression3.csv #remplace les ; par des 0
    sed -i 's/ /;/g' presion3.csv #remplace les ' ' par des points virgules
    tail -n +2 pression3.csv > pression3t.csv
    ./test "$a" "$x" pression3t.csv pression3.dat
    cat pression3.dat
    fi
if [ "$w" -eq "1" ]; then #trace un graphique des vents
    a="w"
    if [ -e meteoloca.csv ]; then
        cut -d ";" -f 1,4,5 meteoloca.csv > vent.csv
    else
        cut -d ";" -f 1,4,5 meteo.csv > vent.csv
     fi
     sed -i -r 's/;/ 0/g' vent.csv #remplace les ; par des 0
     sed -i 's/ /;/g' vent.csv #remplace les ' ' par des points virgules
     tail -n +2 vent.csv > ventt.csv
     ./test "$a" "$x" ventt.csv vent.dat
     gnuplot "wind.p"
    fi
if [ "$h" -eq "1" ]; then #graphique en fonction des altitudes
   a="h"
    if [ -e meteoloca.csv ]; then
        cut -d ";" -f 1,14 meteoloca.csv > meteoalt.csv
    else
        cut -d ";" -f 1,14 meteo.csv > meteoalt.csv
    fi
    sed -i -r 's/;/ 0/g' meteoalt.csv #remplace les ; par des 0
    sed -i 's/ /;/g' meteoalt.csv #remplace les ' ' par des points virgules
    tail -n +2 meteoalt.csv > meteoaltt.csv
    ./test "$a" "$x" meteoaltt.csv meteoalt.dat
    cat meteoalt.dat
    fi
if [ "$m" -eq "1" ]; then # en fonction de l humidité
    a="m"
    if [ -e meteoloca.csv ]; then
        cut -d ";" -f 1,6 meteoloca.csv > humidite.csv
    else
        cut -d ";" -f 1,6 meteo.csv > humidite.csv
        fi
    sed -i -r 's/;/ 0/g' humidite.csv #remplace les ; par des 0
    sed -i 's/ /;/g' humidite.csv #remplace les ' ' par des points virgules
    tail -n +2 humidite.csv > humiditet.csv
    ./test "$a" "$x" meteohumiditet.csv meteohumidite.dat
    gnuplot "hum.p"
    fi
    rm meteoloca.csv #supprime les fichiers de transition
    rm pression.csv
    rm t1.csv
    rm t2.csv
    rm pression.csv
    rm pression2.csv
    rm pression3.csv
    rm t3.csv
    rm meteoalt.csv
    rm wind.csv
    rm humidite.csv
