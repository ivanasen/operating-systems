#/bin/bash

# Exercise 1 Problem 3

# Изведете списък на файлове в цялата файлова система, които са с име f1 и
# собственик s81xxx. Разпечатайте съдържанието им на екрана.

find / -name f1 -user s81837 | xargs cat

# or
find / -name f1 -user s81837 -exec cat {} \;

# or
find / -name f1 -user s81837 -exec cat {} +

