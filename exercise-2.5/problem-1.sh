#!/bin/bash

# Exercise 2 Problem 1

# Да се въведат от клавиатурата три реда съдържащи Hello world, името ви и
# днешната дата. Да се запише тази информация в 5 файла с имена a1-a5. В
# новосъздадена директория FIRST поддиректория на текущата директория да се
# прехвърлят първите 2 файла, като ги изведете сортирани на екрана. Да се
# създаде поддиректория на FIRST – SECOND. Да се копират останалите три файла в
# последната директория. Да се изведе на екрана първите 3 символа от всеки
# ред на файл а3 и последния ред на а4. Да се изведе съдържанието на файла
# hello.c от началната потребителска директория.

tee a{1..5}

mkdir FIRST

mv a1 a2 FIRST
sort FIRST/a1 FIRST/a2

cp a* FIRST/SECOND

cut a3 -c1-3
tail a4 -n 1

cat /student/hello.c

