#!/bin/bash

# Да се изтрие директория BB. Да се изведе съдържанието на главната директория
# на екрана. Да се изведе информация какво е съдържанието на всички файлове от
# HOME директорията. Да се отреже от файловете а1 и а2 първите 3 символа на
# всеки ред и да се изведат на екрана, а файла а5 да се върне обратно в
# началната потребителска директория. Да се сравнят файловете а3 и а4
# посимволно. Да се изведе размера в байтове на всички файлове от директория
# /home/KN, чието име е а1.

rm -rf BB

ls /

find ~ -exec file {} \;

cut FIRST/a1 FIRST/a2 -c3-

mv FIRST/SECOND/a5 ~

cmp a3 a4

find /home/KN -name a1 | xargs wc -c
# or
find /home/KN -name a1 -exec wc -c {} \;
# or
find /home/KN -name | xargs du -a
# or in "human readable format"
find /home/KN -name | xargs du -a -h

