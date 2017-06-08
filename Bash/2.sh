#!/bin/bash
for pid in $(pidof bash); 
do
proc=$(</proc/$pid/status) ;
 printf "\033[48;5;1m  $pid \033[m , $proc \n \n" ; 
done
