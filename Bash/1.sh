#!/bin/bash
# uptime.sh

while [ 1 ]
do
uptime=$(</proc/uptime)
uptime=${uptime%%.*}
#power= $(/org/freedesktop/UPower/devices/battery_BAT1)

seconds=$(( uptime%60 ))
minutes=$(( uptime/60%60 ))
hours=$(( uptime/60/60%24 ))
days=$(( uptime/60/60/24 ))

net=$(ifstat -i wlp7s0 -q 1 1)

battery=$( upower -i /org/freedesktop/UPower/devices/battery_BAT1 | grep -E 'state|to\  full| percentage')
echo " $days days, $hours hours, $minutes minutes, $seconds seconds,
$battery
$net

" 
#sleep 1
done

