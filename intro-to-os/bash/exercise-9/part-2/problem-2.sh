#!/bin/bash

# Да се състави командна процедура, която получава като параметри
# в командния ред при стартиране акаунти на потребители. Чете от стандартния вход
# символен низ го изпраща на всеки от подадените потребители, които са активни в
# текущия момент. / MESS_USERS/

users=$*
read msg

logged_in=$(who | cut -d ' ' -f 1)

for user in $users; do
    (echo $logged_in | grep "$user" >/dev/null) &&
        (echo $msg | write $user)
done

