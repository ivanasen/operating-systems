#!/bin/bash

# Exercise 2 Problem 3

# От файла /etc/passwd да се изведат имената на всички студенти, ползващи
# системата Линукс, както специалност, курс и група.

# Probably that info is stored in the username itself, so outputing it
cat /etc/passwd | cut -d : -f 1

