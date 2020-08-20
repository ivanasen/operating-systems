#!/bin/bash

# създайте две директории aa и bb. вземете от /home/student двета файла hello.c
# и second.c. изведете съдържанието на първия на екрана, а на втория изведете
# размера в байтове. прехвърлете първия в едната директория, а втория в другата.
# направете копие на втория и изтрийте оригинала.


mkdir AA BB
cp /home/student/hello.c /home/student/second.c .

cat hello.c
wc -c second.c

mv hello.c AA
mv second.c BB
mv BB/second.c BB/second_copy.c
rm BB/second.c

