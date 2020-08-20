#!/bin/bash

# Създайте 5 копия на даден файл, разпечатайте редовете,
# в които се среща регулярния израз int в този файл и 
# във файловете hello.c и second.c и изведете техния брой.

# Local environment so using other files and '#' instead of 'int'
(cat problem-1.sh
    | tee problem-1-copy-{1..5}.sh
    | cat; cat problem-2.sh problem-3.sh) | grep '#'

