#!/bin/bash

declare -a numbers

while read -a numbers; do
    first=${numbers[0]}
    second=${numbers[1]}
    last=${numbers[-1]}

    echo ${numbers[$((${#numbers[@]}-1))]}

    if [ "$last" -lt "$(($((first+second))/2))" ]; then
	echo ${numbers[@]}
    fi
done < p3a.txt


