#!/bin/bash

# От стандартния вход се въвеждат три имена на файлове.
# Във файла – len извеждате  брая на буквите в името им,
# а във файла size – размера

read f1
read f2
read f3

expr length $f1 + length $f2 + length $f3 > len
wc -c $f1 $f2 $f3 > size
