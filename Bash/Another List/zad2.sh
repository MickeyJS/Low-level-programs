#!/bin/bash
#Skrypt śledzący stronę internetową.

lynx -dump $1 > strona1

while [ 1 ]
do
	lynx -dump $1 > strona2
	diff strona1 strona2 > zmiany
	if [ -s zmiany ]
	then 
	gxmessage -title "Zmiana na stronie" -bg black -center -fg green -buttons "Tak:8,Nie:9" "Dokonano zmiany na obserwowanej przez Ciebie stronie. Czy wyświetlić zmiany?"
	#else  ##### Opcjonalnie, do wyświetlania komunikatu o braku zmian
	
	#gxmessage -title "Brak zmiany na stronie" -bg black -center -fg green "Brak zmiany na obserwowanej przez Ciebie stronie."
	#nie ma zmian :( 	

	fi
	
	if [ $? -eq 8 ]
		then gxmessage -title "Wyświetlam zmianę:" -bg black -center -fg green -file zmiany
fi
	> strona1
	cat strona2 > strona1
	>strona2
	>zmiany
	sleep $2
done
	
