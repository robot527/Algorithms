#! /bin/bash 

cc -g sl_list.c sl_list_test.c

if test -e "a.out";then
	valgrind --version &> /dev/null
	if test $? == 0;then
		valgrind --verbose --leak-check=full --show-leak-kinds=all ./a.out
	else
		./a.out
	fi
	rm a.out
fi
