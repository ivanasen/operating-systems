#!/bin/bash

# Да се състави командна процедура, която получава при стартиране
# в командния ред два параметъра – имена на съществуващи директории.
# В случай , че общият брой на файловете, съдържащи изходен текст на Си
# в двете директории надвишава 20, процедурата създава в текушата
# директория файл – sources.txt, съдържащ имената им, който да е достъпен само за
# четене на всички потребители. В противен случай извежда с подходящо съобщение
# този брой на стандартния изход.

dir1=$1
dir2=$2

dir1_cfiles=$(find $dir1 -name "*.c")
dir2_cfiles=$(find $dir2 -name "*.c")
dir1_count=$(echo "$dir1_cfiles" | wc -l)
dir2_count=$(echo "$dir2_cfiles" | wc -l)

total_count=$(expr $dir1_count + $dir2_count)
if [[ $total_count -le 20 ]]; then
    echo "Total *.c files count: $total_count"
    exit 0
fi

echo "$dir1_cfiles" > sources.txt
echo "$dir2_cfiles" >> sources.txt
chmod 444 sources.txt

