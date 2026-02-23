#!/bin/bash
[ "$#" -eq 0 ] && echo "No arguments provided" && exit 0
read -p "Please enter an integer: " integer

[ "$integer" -le "$#" ] && { yy="${!integer}"; echo "The argument at position $integer is: $yy"; } || echo "No argument has been provided at position $integer."
