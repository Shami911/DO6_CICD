#!/bin/bash
if [ ! -f "./test" ]; then 
    echo "File not found"
    exit 1
fi 
for i in {1..7}; do
    test_integrate=$(case $i in
    1) echo "Learning to Linux" ;;
    2) echo "Learning to work with Network" ;;
    3) echo "Learning to Monitoring" ;;
    4) echo "Learning to extra Monitoring" ;;
    5) echo "Learning to Docker" ;;
    6) echo "Learning to CI/CD" ;;
    7) echo "Bad number!"
    esac)
    original_file=$(./test $i);
    if [ "$original_file" = "$test_integrate" ]; then
        echo -e "Test $i\033[32m SUCCESS\033[0m" ;
    else 
        echo "Test error"
    fi
done
for i in {8..10}; do
    original_file=$(./test $i);
    test_integrate="Bad number!"
    if [ "$original_file" = "$test_integrate" ]; then
        echo -e "Test $i\033[32m SUCCESS\033[0m" ;
    fi
done