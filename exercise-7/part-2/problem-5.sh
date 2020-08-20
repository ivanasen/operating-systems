#!/bin/bash

# Да се състави командна процедура, която  приема като параметър
# в командния ред име на потребител. Процедурата прекратява 
# изпълнението на всички активни процеси на дадения потребител и извежда техния брой.

usr=$1

processes=$(ps -u $usr -o pid= | tr -d ' ')

for p in $processes; do
    kill -9 $p
done