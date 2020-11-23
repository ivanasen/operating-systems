#!/bin/bash

# В директория /home/KN/student се намира файл f_niz със съдържание символен низ.
# Да се състави командна порцедура, която получава три позиционни
# параметъра – две имена на директории и един символен низ.
# Ако не е подаден символен низ се взима низа, от посочения по-горе файл.
# Процедурата прехвърля всички файлове от текушата директория с разщирение .с
# в първата подадена директория, а тези с разширение .out  във втората.
# Извежда на стандартния изход с подходящо съобщение общия брой на непрехвърлените
# файлове. Създава директория с име подадения низ, ако такава несъществува.
# Записва в нея във файл names имената на всички прехвърлени файлове.

# Local env so using test file ff in current directory

# First part is duplicate of exercise-7/part-2/problem-6.sh
dir1=$1
dir2=$2

expr $# \> 2 >/dev/null && str=$3 || str=$(cat f_niz)

files_to_move=$(ls | grep -e '.*\.c$\|.*\.out$')
mv *.c $dir1
mv *.out $dir2

echo -n 'Not moved files count: '
find . -maxdepth 1 -type f | wc -l

# Second part

# Can also use 'mkdir -p $str' but if
# str == bar/foo => folder foo will also be created inside bar
[[ -d $str ]] || mkdir $str

echo "$files_to_move" > $str/names
