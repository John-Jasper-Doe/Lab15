#!/bin/bash

cat rnd.txt | ./kkmeans -k 3 > rnd_out.csv
gnuplot -e "set title 'OutData';set ylabel 'Y-axis';set xlabel 'X-axis';set grid;set term png size 1024,960;set output 'rnd_result.png';set datafile separator ';';set palette model RGB defined (0 'red',1 'blue', 2 'green', 3 'black', 4 'yellow', 5 'brown');plot 'rnd_out.csv' using 1:2:3 notitle with points pt 7 palette"

