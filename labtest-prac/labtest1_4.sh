#!/bin/bash

amount=$1
high=$((amount+2))
low=$((amount-2))

while read -r product_id product_name price inventory; do
    if [ "$inventory" -le "$high" ] && [ "$inventory" -ge "$low" ]; then
	echo "$product_id $product_name"
    fi
done < inva.txt
