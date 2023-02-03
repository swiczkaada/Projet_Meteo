set output "t1oup1.jpg"
set autoscale noextend
set grid nopolar
set style data lines
set xlabel "ID de station"
set ylabel "Temperatures"
set datafile separator ";"
set xrange [*:*]
set yrange [*:*]
set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front noinvert bdefault
set xtics rotate by 90 right
Shadecolor = "#80E0A080"
plot "pression1.dat" using 0:1:11:xticlabels(3) with filledcurve fc rgb Shadecolor title "Temperatures min max",'' using 0:6 smooth mcspline lw 2 title "Temperatures moy"
pause -1 "Hit return to continue"
