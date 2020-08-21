#!/bin/bash

# Да се състави командна процедура, която получава в командния ред
# при стартиране име на текстов файл и списък от идентификатори на
# потребители на системата. Процедурата изпраща съдържанието на файла
# на онези от потребителите от списъка, които са стартирали сесия и са
# позволили писане. При повече от една сесия на потребител съобщението
# да се изпрати към най-скоро ползвания терминал. Ако текущият потребител
# е забранил изпращането на съобщения настройката му да се промени,
# за да приключи процедурата и след това да се върне забраната.

# This must be run as root in order to be able to enable messages for other users.

file=$1
shift 1
users=$*

logged_in=$(who | cut -d ' ' -f 1)
msg=$(cat $file)

for user in $users; do
    (echo "$logged_in" | grep "$user" &>/dev/null) || continue
    
    # write sends messages to the most recent terminal by default
    (echo "$msg" | write $user) ||
        (runuser -l $user -c "mesg y" &&
            echo "$msg" | write $user &&
            runuser -l $user -c "mesg n")
done

