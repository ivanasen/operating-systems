#!/bin/bash

# Да се състави командна процедура, която получава като позиционни параметри
# име на файл и акаунти на потребители. Прочита съобщение от стандартния вход
# и заедно със съдържанието на файла го изпраща на всички потребители,
# които са стартирали сесия и чийто акаунти са измежду подадените.

file=$1
shift 1
users=$*

read msg
msg+=$'\n'
msg+=$(cat $file)

active_users=$(who | cut -d ' ' -f 1)

for user in $active_users; do
    if (echo $users | grep "$user" &>/dev/null); then
        printf "$msg" | write $user
    fi
done

