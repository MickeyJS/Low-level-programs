#!/bin/bash
#Skrypt-nakładka do polecenia cp (pokazuje dodatkowo skopiowaną liczbę bajtów i ETA).
#Argumenty przy wywołaniu należy podać tak samo jak dla polecenia cp (bez obsługi parametrów)


ROZM_PLIKU1=$(stat -c%s $1)
>$2
ROZM_PLIKU2=0
CZAS_ROZP=$(date +%s)
CZAS_AKT=0
ROZNICA_ROZM=1
ROZNICA_ROZM2=0
PREDKOSC=0
ZOSTALO=0

cp -f $1 $2 &
echo
while [ $ROZM_PLIKU1 -gt $ROZM_PLIKU2 ] ; do	
	ROZM_PLIKU2=$(stat -c %s $2)
	CZAS_AKT=$(date +%s)
	ROZNICA_ROZM2=$ROZNICA_ROZM
	ROZNICA_ROZM=$(( $ROZM_PLIKU2 - $ROZNICA_ROZM2 ))
	PROCENT=$((( 100 * $ROZM_PLIKU2 ) / $ROZM_PLIKU1 ))
	ZOSTALO=$((( $ROZM_PLIKU1 - $ROZM_PLIKU2 ) /$ROZNICA_ROZM ))
	echo -n -e " \r Skopiowano $PROCENT%, prędkość: $ROZNICA_ROZM B/s, pozostało $ZOSTALO s."
sleep 1
done
echo
