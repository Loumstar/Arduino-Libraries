#!/bin/bash

for test in "$@"
do
    echo -e "\n\nTESTING: $test\n"
    ./$test
    
    if [ $? -ne 0 ]
    then
        echo -e "TEST FAILED. STOPPING."
        break
    else
        echo -e "TEST PASSED."
    fi
done