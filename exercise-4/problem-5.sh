#!/bin/bash

# Изведете в обратен ред по времето на създаване само файловете
# от текущата директория, чийто имена започват с f и завършват на .с.
# Изведете правата за достъп  на всеки файл и ги запишете в друг файл. 

# Local env so printing files which start with p and end with .sh
ls -t -r p*.sh
    | tee >(cat)
    | ll
    | tail -n +2
    | tr -s ' '
    | cut -d ' ' -f 1,9 > perms.out

