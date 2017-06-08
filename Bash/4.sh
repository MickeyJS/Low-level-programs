#!/bin/bash
#Skrypt wyszukujący takie same pliki (md5sum)
$1
find $1 -type f -exec md5sum '{}' ';' | sort | uniq --all-repeated=separate -w32
