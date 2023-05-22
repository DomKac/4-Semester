#!/bin/bash

m=$1

rm dane/select_min_k3.txt
rm dane/select_mid_k3.txt
rm dane/select_max_k3.txt

rm dane/select_min_k5.txt
rm dane/select_mid_k5.txt
rm dane/select_max_k5.txt

rm dane/select_min_k7.txt
rm dane/select_mid_k7.txt
rm dane/select_max_k7.txt

rm dane/select_min_k9.txt
rm dane/select_mid_k9.txt
rm dane/select_max_k9.txt


echo "n przestawienia porównania czas" >> dane/select_min_k3.txt
echo "n przestawienia porównania czas" >> dane/select_mid_k3.txt
echo "n przestawienia porównania czas" >> dane/select_max_k3.txt

echo "n przestawienia porównania czas" >> dane/select_min_k5.txt
echo "n przestawienia porównania czas" >> dane/select_mid_k5.txt
echo "n przestawienia porównania czas" >> dane/select_max_k5.txt

echo "n przestawienia porównania czas" >> dane/select_min_k7.txt
echo "n przestawienia porównania czas" >> dane/select_mid_k7.txt
echo "n przestawienia porównania czas" >> dane/select_max_k7.txt

echo "n przestawienia porównania czas" >> dane/select_min_k9.txt
echo "n przestawienia porównania czas" >> dane/select_mid_k9.txt
echo "n przestawienia porównania czas" >> dane/select_max_k9.txt

for n in {100..10000..100}
do
	min=$(echo 1)
    mid=$(echo $n /2 | bc)
    max=$n
    echo "min = $min, max = $max, mid = $mid"
    for i in $( eval echo {1..$m} )
    do
        ./rtab $n >> dane/randomtab.txt

        cat dane/randomtab.txt | ./sel3 $min 3 >> dane/select_min_k3.txt
        cat dane/randomtab.txt | ./sel3 $mid 3 >> dane/select_mid_k3.txt
        cat dane/randomtab.txt | ./sel3 $max 3 >> dane/select_max_k3.txt

        cat dane/randomtab.txt | ./sel3 $min 5 >> dane/select_min_k5.txt
        cat dane/randomtab.txt | ./sel3 $mid 5 >> dane/select_mid_k5.txt
        cat dane/randomtab.txt | ./sel3 $max 5 >> dane/select_max_k5.txt

        cat dane/randomtab.txt | ./sel3 $min 7 >> dane/select_min_k7.txt
        cat dane/randomtab.txt | ./sel3 $mid 7 >> dane/select_mid_k7.txt
        cat dane/randomtab.txt | ./sel3 $max 7 >> dane/select_max_k7.txt

        cat dane/randomtab.txt | ./sel3 $min 9 >> dane/select_min_k9.txt
        cat dane/randomtab.txt | ./sel3 $mid 9 >> dane/select_mid_k9.txt
        cat dane/randomtab.txt | ./sel3 $max 9 >> dane/select_max_k9.txt

        rm dane/randomtab.txt
    done
done