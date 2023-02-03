rest
set terminal jpeg size 1600,1200
set output "wind.jpg"
set autoscale noextend
set style data lines
set title "carte des vents"
set xlabel 'station'
set ylabel 'vent'
set xrange [ -180 : 180 ]
set yrange [ -90 : 90 ]
set isosam 31,31
NO_ANIMATION = 1
set palette defined (0 "white", 1 "blue", 2 "red")
set datafile separator ";"
plot "vent.dat" u 1:2:(3*$3):(sin(column(2))) with vectors
quitrest
set terminal jpeg size 1600,1200
set output "wind.jpg"
set autoscale noextend
set style data lines
set title "carte des vents"
set xlabel 'station'
set ylabel 'vent'
set xrange [ -180 : 180 ]
set yrange [ -90 : 90 ]
set isosam 31,31
NO_ANIMATION = 1
set palette defined (0 "white", 1 "blue", 2 "red")
set datafile separator ";"
plot "vent.dat" u 1:2:(3*$3):(sin(column(2))) with vectors
quit
