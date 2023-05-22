#!/bin/bash

m=$1

rm dane/select_min_m$m.txt
rm dane/select_mid_m$m.txt
rm dane/select_max_m$m.txt

rm dane/randomselect_min_m$m.txt
rm dane/randomselect_mid_m$m.txt
rm dane/randomselect_max_m$m.txt

echo "n przestawienia porównania" >> dane/select_min_m$m.txt
echo "n przestawienia porównania" >> dane/select_mid_m$m.txt
echo "n przestawienia porównania" >> dane/select_max_m$m.txt

echo "n przestawienia porównania" >> dane/randomselect_min_m$m.txt
echo "n przestawienia porównania" >> dane/randomselect_mid_m$m.txt
echo "n przestawienia porównania" >> dane/randomselect_max_m$m.txt


for n in {100..10000..100}
do
	min=$(echo 1)
    mid=$(echo $n /2 | bc)
    max=$n
    echo "min = $min, max = $max, mid = $mid"
    for i in $( eval echo {1..$m} )
    do
        ./rtab $n >> dane/randomtab.txt
        cat dane/randomtab.txt | ./sel $min >> dane/select_min_m$m.txt
        cat dane/randomtab.txt | ./sel $mid >> dane/select_mid_m$m.txt
        cat dane/randomtab.txt | ./sel $max >> dane/select_max_m$m.txt

        cat dane/randomtab.txt | ./randsel $min >> dane/randomselect_min_m$m.txt
        cat dane/randomtab.txt | ./randsel $mid >> dane/randomselect_mid_m$m.txt
        cat dane/randomtab.txt | ./randsel $max >> dane/randomselect_max_m$m.txt
        rm dane/randomtab.txt
    done
done