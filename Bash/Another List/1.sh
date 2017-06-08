#!/bin/bash
cat /proc/net/dev | cat /proc/uptime | cat /sys/class/power_supply/BAT1/capacity 

