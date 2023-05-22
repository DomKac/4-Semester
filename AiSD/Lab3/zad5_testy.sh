#!/bin/bash

m=$1

rm dane/QS_worst_m$m.txt    
rm dane/QSS_worst_m$m.txt
rm dane/DPQS_worst_m$m.txt  
rm dane/DPQSS_worst_m$m.txt


echo "n porównania przestawienia czas" >> dane/QS_worst_m$m.txt      
echo "n porównania przestawienia czas" >> dane/QSS_worst_m$m.txt
echo "n porównania przestawienia czas" >> dane/DPQS_worst_m$m.txt     
echo "n porównania przestawienia czas" >> dane/DPQSS_worst_m$m.txt


for n in {100..10000..100}
do
    echo "przejscie $n"
    ./dtab $n >> dane/descendingTab.txt
    cat dane/descendingTab.txt | ./qs    >> dane/QS_worst_m$m.txt      
    cat dane/descendingTab.txt | ./qss   >> dane/QSS_worst_m$m.txt
    cat dane/descendingTab.txt | ./dpqs  >> dane/DPQS_worst_m$m.txt      
    cat dane/descendingTab.txt | ./dpqss >> dane/DPQSS_worst_m$m.txt
    rm dane/descendingTab.txt
done
