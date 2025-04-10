#!/bin/bash

tekst=""
slownik="wejscieSkrypt3.in"

read -p "Podaj tekst do sprawdzenia" tekst

for word in $tekst; do
    if (grep -iq "\b$word\b" "$slownik"); then
        echo -e -n "\e[32m$word \e[0m"
    else
        echo -e -n "\e[31m$word \e[0m"
    fi
done