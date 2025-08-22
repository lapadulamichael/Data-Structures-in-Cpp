#!/bin/bash

ERROR=0

echo "Vérification mémoire"

for TEST in 01_arbreAVL 02_arbreAVL 03_arbreAVL 06_arbreAVL 07_arbreAVL 08_arbreAVL 09_arbreAVL
do
	valgrind --tool=memcheck --quiet --error-exitcode=1 ./$TEST > /dev/null 2>&1
        RET=$?
        if [ $RET -eq 0 ]
        then
                echo -e "\t$TEST \xE2\x9C\x94"
        else
                echo -e "\t$TEST"
        fi
        ERROR=$(( ERROR + $RET ))
done

echo -e "\tTotal erreurs/fuites mémoire : $ERROR"
