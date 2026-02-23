#!/bin/bash

input1=$(($1+$((5-$(($1%5))))))
input2=$2

until [ $input1 -gt $((input2-1)) ]
do
	echo -n "$input1 "
	input1=$((input1+5))
done

echo ""
