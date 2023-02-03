set output "humidité.jpg"
set terminal jpeg
set title "carte humidité"
set xlabel "longitude "
set ylabel "lattitude"
set zlabel "altitude"
set xrange [*:*]
set yrange [*:*]
set autoscale noextend
set view map scale 1
set dgrid3d 50,50
set pm3d map interpolate 5,5 flush begin nohidden3d
splot "meteohumidite.dat" using  with pm3d notitle
set palette definded (0 "white",1 "blue",2 "red")
set term png
replot
