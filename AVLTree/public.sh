#!/bin/bash

ERROR=0

echo "Tests classe Historique et TP2"

for i in $(seq 0 7)
do
	diff -Z <(./tp2 demo$i.txt) resultat$i.txt > /dev/null 2>&1
        RET=$?
        if [ $RET -eq 0 ]
        then
                echo -e "\tdemo$i.txt \xE2\x9C\x94"
        else
                echo -e "\tdemo$i.txt"
        fi
        ERROR=$(( ERROR + $RET ))
done

echo -e "\tTotal tests échoués : $ERROR"
