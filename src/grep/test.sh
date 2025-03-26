#!/bin/bash

make s21_grep

first_file="test_case_cat.txt"
test_1=$(grep "" $first_file)
test_1_my=$(./s21_grep "" $first_file)

if [ "$test_1" = "$test_1_my" ]
then
    echo -e "default_test: \033[32mSUCCESS\033[0m"
else
    echo -e "default_test: \033[31mFAIL\033[0m"
fi

echo

for flags in "-i" "-v" "-c" "-l" "-n" "-o"
do
    test_2=$(grep "test" $flags $first_file)
    test_2_my=$(./s21_grep "test" $flags $first_file)
    
    if [ "$test_2" = "$test_2_my" ]
    then
        echo -e "flags_test ($flags): \033[32mSUCCESS\033[0m"
    else
        echo -e "flags_test ($flags): \033[31mFAIL\033[0m"
    fi
done

rm -r s21_grep
