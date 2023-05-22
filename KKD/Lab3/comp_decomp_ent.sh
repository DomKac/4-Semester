#!/bin/bash

kod=$1
plik=$2
skomp=$3

$1 | ./comp $2
echo "Entropia $2 : "
./ent $2
printf "\nEtropia skompresowany_plik.bin: \n"
./ent $3
printf "\n"

     