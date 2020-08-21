#!/bin/bash

# От стандартния вход се въвежда  символен низ състоящ се от четири думи.
# Изведете позицията на първото срещане на буквата „а“ в него.
# Изведете подстринг от него от позиция 5 в дължина 10.

read str
echo -n "First place of 'a': "
expr index "$str" 'a'
echo -n "Substring from pos 5 with len 10: "
expr substr "$str" 5 10
