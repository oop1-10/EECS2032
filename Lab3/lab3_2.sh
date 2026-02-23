#!/bin/bash

generate_random_number() {
    return $(( (RANDOM % 100) + 1 ))
}

play_game() {
    echo -n "Welcome to the Number Guessing Game! I have selected a number between 1 and 100.  Can you guess it?  "

    let input=-1
    let attempts=1
    until [ "$input" -eq "$1" ]
    do
	  read -p "Enter your guess (or type 'exit' to quit): " input

	  if [ "$input" = "exit" ]; then
	      echo "Thank you for playing!  The number was: $1"
	      exit 0
	  elif [[ "$input" =~ ^-?[0-9]+$  ]]; then
	      if [ "$input" -eq "$1" ]; then
		 echo "Congratulations!  You've guessed the number $1 in $attempts attempts."
	      elif [ "$input" -gt "$1" ]; then
		  echo "Too high!  Try again."
	      else
		  echo "Too low!  Try again."
	      fi
	  else
	      echo "Please enter a valid number."
	  fi
	  attempts=$((attempts+1))
    done
}

generate_random_number
play_game $?
