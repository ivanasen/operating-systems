#!/bin/bash

# Изведете само имената, потока и групата
# на всички студени специалност КН от файла /etc/passwd.

# Most likely that info is stored in the comment field of /etc/passwd.
cat /etc/passwd | cut -d : -f 5

