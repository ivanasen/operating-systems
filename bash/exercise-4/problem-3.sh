#!/bin/bash

cat problem-1.sh problem-2.sh |
    sort > merge.out ;
    wc -c problem-1.sh problem-2.sh merge.out
