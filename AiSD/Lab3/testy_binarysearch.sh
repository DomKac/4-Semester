#!/bin/bash

m=$1

rm dane/BS_poczatek_m$m.txt
rm dane/BS_koniec_m$m.txt
rm dane/BS_srodek_m$m.txt
rm dane/BS_losowy_m$m.txt
rm dane/BS_spoza_m$m.txt


echo "n porównania czas" >> dane/BS_poczatek_m$m.txt
echo "n porównania czas" >> dane/BS_koniec_m$m.txt
echo "n porównania czas" >> dane/BS_srodek_m$m.txt
echo "n porównania czas" >> dane/BS_losowy_m$m.txt
echo "n porównania czas" >> dane/BS_spoza_m$m.txt


for n in {1000..100000..1000}
do
	limit0=$(echo 0)
    limit1=$(echo "($n /10) - 1" | bc)          # 'blisko początku'
    limit2=$(echo "$n - ($n /10) - 1" | bc)     # 'blisko końca'
    limit3=$(echo "$n - 1" | bc)                # ostatni indeks tablicy
    limit4=$(echo "($n/2) - ($n /10)" | bc)     # 'okolo środka'
    limit5=$(echo "($n/2) + ($n /10)" | bc)
    echo "przejscie $n"
    for i in $( eval echo {1..$m})
    do
        ./rtab $n >> dane/randomtab.txt
        # 'blisko początku'
        cat dane/randomtab.txt | ./bs $limit0 $limit1 >> dane/BS_poczatek_m$m.txt      
        # 'blisko końca'
        cat dane/randomtab.txt | ./bs $limit2 $limit3 >> dane/BS_koniec_m$m.txt
        # 'okolo środka'
        cat dane/randomtab.txt | ./bs $limit4 $limit5 >> dane/BS_srodek_m$m.txt
        # 'losowy z całej tablicy'
        cat dane/randomtab.txt | ./bs $limit0 $limit3 >> dane/BS_losowy_m$m.txt
        # 'spoza tablicy'
        cat dane/randomtab.txt | ./bs $limit0 $limit0 >> dane/BS_spoza_m$m.txt

        rm dane/randomtab.txt
    done
done
