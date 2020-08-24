#!/bin/bash

cat kkmeans_ex.txt | ./kkmeans -k 3 > kkmeans_out.csv
gnuplot -e "set title 'kkmeans';set ylabel 'Y-axis';set xlabel 'X-axis';set grid;set term png size 1024,960;set output 'kkmeans_result.png';set datafile separator ';';set palette model RGB defined (0 'red',1 'blue', 2 'green', 3 'black', 4 'yellow', 5 'brown');plot 'kkmeans_out.csv' using 1:2:3 notitle with points pt 7 palette"

