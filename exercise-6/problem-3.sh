#!/bin/bash

# Изведете броя на файловете в текущата директория,
# с права на достъп 644 и отпечатайте само имената им.

files=$(find . -perm 644)
echo -n 'Files count: '
echo $files | wc -l
echo $files
