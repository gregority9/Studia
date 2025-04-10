#!/bin/bash

tekst="";
slownik="wejscieSkrypt3.in"

read -p "Podaj tekst do sprawdzenia: " tekst

for word in $tekst; do
    if !(grep -iq "\b$word\b" "$slownik"); then
        echo "$word"
    fi
done