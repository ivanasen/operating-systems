#!/bin/bash

# Създайте файл с имена на студенти.
# Сортирайте го и го изпратете на един от потребителите в системата,
# като подмените малките с главни букви/ команда tr/

sort names.txt | tr '[:lower:]' '[:upper:]' | write pesho

