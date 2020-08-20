#!/bin/bash

# Да се състави командна процедура, която получава като параметри в командния ред
# имена на съществуващи текстови файлове. Прочита от стандартния вход
# символен низ и за всеки от зададените файлове извежда по подходяш начин
# на стандартния изход броя на редовете които съдържат низа.

files=$*
read str

for file in $files; do
    count=$(grep "$str" $file | wc -l)
    echo "File '$file': $count"
done

