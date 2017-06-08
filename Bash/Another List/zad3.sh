#!/bin/bash
#Skrypt wyszukujący takie same pliki (md5sum)

find $! -type f -exec md5sum '{}' ';' | sort | uniq --all-repeated=separate -w32
