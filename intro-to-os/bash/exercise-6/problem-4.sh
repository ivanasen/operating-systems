#!/bin/bash

# Чете от страдантния вход имената на двама потребителя.
# Изведете броя на логическите терминали, на които не
# работят потребители с указаните имена.

read usr1
read usr2

who | cut -d ' ' -f 1 | sed -E "/$usr1|$usr2/d"
# or
who | cut -d ' ' -f 1 | grep -v "$usr1\|$usr2"
