
FLAG = -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE
CHECK = 2>&1 valgrind --tool=memcheck --leak-check=yes

all: s21_cat 

s21_cat: Makefile s21_cat.h s21_cat.c
	gcc $(FLAGS) s21_cat.c -o s21_cat

check:
	clang-format -style=Google -n *.c

clean:
	rm -f s21_cat

valgrind: s21_cat
	$(CHECK) ./s21_cat $(FILE) > valgrind.log 2>&1

chmod:
	chmod +x test.sh

