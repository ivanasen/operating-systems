#!/bin/bash

# Да се състави командна процедура, която получава в командния ред
# при стартиране един параметър – символен низ. Ако несъшествува директория
# с подаденото име в началната потребителска директория, процедурата я създава.
# Копира в тази директория всички обикновени файлове от текушата директория,
# които са достъпни за четене и писане и извежда на стандартния изход броя на останалите.

str=$1

[[ -d $HOME/$str ]] || mkdir $HOME/$str

files=$(find . -type f -perm /666)
# Subtract 1 to remove current directory entry from find call
total_count=$(expr $(find . | wc -l) - 1)

cp $(echo "$files" | tr "\n" " ") $HOME/$str

rem_count=$(expr $total_count - $(echo "$files" | wc -l))
echo $rem_count

