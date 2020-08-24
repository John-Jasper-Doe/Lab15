#!/bin/bash

cat sky.txt | ./kkmeans -k 3 > sky_out.csv
gnuplot -e "set title 'sky' textcolor rgbcolor 'white';set ylabel 'Y-axis';set xlabel 'X-axis';set grid;set term png size 1024,960;set output 'sky_result.png';set datafile separator ';';set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor 'black' behind;set border linecolor rgbcolor 'white';set key textcolor rgbcolor 'white';plot 'sky_out.csv' using 1:2 notitle with points pt 7 linecolor rgb'white'"

