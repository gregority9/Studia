#!/bin/bash

# tester.sh - skrypt ktory sprawdza poprawnosc wynikow z tym co jest w .out
# Do dzialania skryptu wymagane sa:
# - folder z plikami .in i .out, ktore sa na STOSie w sekcji Testy (na samym dole)
# - polecenie bc, ktore mozesz sprawdzic wpisujac w terminalu bc (i potem quit)
# Uzytkownik skryptu jest odpowiedzialny za uprzednia kompilacje.

# UWAGA! Pliki .out byly edytowane w Windowsie (koncowka linii \r\n zamiast \n)
# Przed uzyciem skryptu nalezy wiec wykonac ponizsza komende:
# sed -i 's/\r$//' wyc_i_gor/*.out
# Pamietaj rowniez o nadaniu odpowiednich uprawnien
# chmod +x tester.sh

# Odpowiednio zmodyfikuj.
nazwaSkompilowanegoProgramu="./main"
testDir="wyc_i_gor"

# Pomiar czasu
# Wielkie podziekowania dla alyxia.dev za podzielenie sie kodem
declare -A _perf_timers

_perf_timer_start() {
  local name="$1"
  if [[ -z "$name" ]]; then
    echo "$0: usage: $0 <name>" >&2
    return 1
  fi
  _perf_timers["$name"]="$(date +%s.%N)"
}

_perf_timer_stop() {
  local stop_time
  stop_time="$(date +%s.%N)"
  local name="$1"
  if [[ -z "$name" ]]; then
    echo "$0: usage: $0 <name>" >&2
    return 1
  fi
  local start_time="${_perf_timers[$name]}"
  unset _perf_timers["$name"]

  local duration
  duration=$(echo "scale=3; ($stop_time - $start_time) * 1000" | bc)
  echo "${duration}"
}

declare -A _time_limits

_time_limits["11"]=10000
_time_limits["12"]=10000
_time_limits["13"]=15000
_time_limits["14"]=15000
_time_limits["15"]=15000
_time_limits["19"]=15000

validateTime() {
  local limit="$1"
  local timeTaken="$2"
  if(( timeTaken < limit )); then
    echo "1"
  else
    echo "0"
  fi
}

# Wykonywanie testow
for input in $(ls "$testDir"/*.in | sort -V); do
  name=$(basename "$input" .in)
  expectedFile="$testDir/$name.out"

  if [[ ! -f "$expectedFile" ]]; then
    echo "Missing expected output file for $input"
    exit 1
  fi

  _perf_timer_start "$name"
  output=$(printf "%s" "$("$nazwaSkompilowanegoProgramu" < "$input")")
  czas=$(_perf_timer_stop "$name")
  expected=$(printf "%s" "$(cat "$expectedFile")")

  czas_int=$(printf "%.0f" "$czas")
  limit=${_time_limits[$name]:-1000}
  isPassingTime="$(validateTime $limit $czas_int)"

  if [[ "$output" != "$expected" || "$isPassingTime" != "1" ]]; then
    echo -e "======= \e[1;31mTest $name FAILED\e[0m ======="
    echo -n "Expected: "
    echo -e "\e[1;32m$expected\e[0m"
    echo -n "Got: "
    if [[ "$output" != "$expected" ]]; then
      echo -e "\e[1;31m$output\e[0m"
    else
      echo -e "\e[1;32m$output\e[0m"
    fi
    echo -n "Time: "
    if [[ "$isPassingTime" != "1" ]]; then
      echo -e "\e[1;31m${czas_int}ms (overtime)\e[0m"
    else
      echo -e "\e[1;32m${czas_int}ms\e[0m"
    fi
    echo "=============================="
  else
    echo -e "\e[1;36mTest $name passed in ${czas_int}ms\e[0m"
  fi
done
