set terminal jpeg
set output "t2oup2.jpg"
reset
set autoscale noextend
set datafile separator ";"
set title ' Temperature moyenne en fonction du temps '
set xlabel "date/heure"
set ylabel "temperature moyenne"
set timefmt '%Y-%m-%d-%H'
set xdata time
set xrange [*:*]
set yrange [*:*]
set xtics rotate by 45 right
set format x '%Y/%m/%d %H'
plot "pression2.dat" using (sprintf("%s-%s",substr(stringcolumn(2),1,10),substr(stringcolumn(2),12,14))):11 with lines
pause -1 "Hit to return"
reset
