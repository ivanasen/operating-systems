#!/bin/bash

# Да се състави командна процедура, която  получава като параметри
# в командния ред име на файл и символен низ. Създайте 3 копия на
# подадения файл, разпечатайте редовете, в които се среща подадения 
# символен низ   в този файл и изведете техния брой във файл, чието име
# се подава от стандартния вход. Преместете файла в поддиректория info
# в родителската директория на началната потребителска директория.

# Call with test args: test.txt ad

file_name=$1
string=$2
read file_lines_count

for i in {1..3}; do
    cp $file_name ${file_name}_copy_$i
done

grep $string $file_name

lines_count=$(grep $string $file_name | wc -l)
echo $lines_count > $file_lines_count

mkdir info
mv $file_lines_count info

