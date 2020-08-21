#!/bin/bash

# Да се състави командна процедура, която получава при стратиране в
# командния ред акаунти на потребители. За всеки от подадените акаунти,
# които са в сесия да се изведе информация от файла /etc/passwd /ACTIV_USERS/

users=$*
logged_in_users=$(who | cut -d ' ' -f 1)

for user in $users; do
    (echo "$logged_in_users" | grep "$user" &>/dev/null) &&
        (cat /etc/passwd | grep $user)
done

