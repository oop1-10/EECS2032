#!/bin/bash

declare -A borrowed_map

while IFS=':' read -r book_id borrowed_count; do
    borrowed_map["$book_id"]=$borrowed_count
done < borrowed.txt


while IFS=':' read -r book_id title author available_count; do
    borrowed_amount=${borrowed_map["$book_id"]}
    
    if [ "$available_count" -lt "$borrowed_amount" ]; then
        echo "$title"
    fi

done < books.txt
