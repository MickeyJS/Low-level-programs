#!/bin/bash
#Skrypt podający sumę i iloczyn mnogościowy dwóch plików.
echo "Podaj nazwe pierwszego pliku: "
read X
echo "Podaj nazwe drugiego pliku: "
read Y

#Różnica

echo "Różnica dla podanych plików:"
echo "------------------------------"
grep -Fxvf $Y $X | sort -u
echo "------------------------------"
# Suma

echo "Suma dla podanych plików:"
echo "------------------------------"
grep -Fxvf $Y $X | sort -u
cat $Y | sort -u
echo "------------------------------"


