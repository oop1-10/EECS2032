#!/bin/bash

if [ "$#" -le 1 ]; then
    echo "You should enter two numbers!"
    exit 1
fi

int1=$1
int2=$2

if [ "$int1" -eq "$int2" ]; then
	echo "These two numbers are equal!"
else
	if [ "$int1" -gt "$int2" ]; then
		max=$int1
		min=$int2
	else
		max=$int2
		min=$int1
	fi

	if [ $[ max % min ] -eq 0 ]; then
		echo "big_num is $((max/min)) times the small_num!"
	else
		echo "No relation!"
	fi
fi
