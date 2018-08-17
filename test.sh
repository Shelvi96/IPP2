#!/bin/bash

for i in $2/*.in; do
	file="${i%.*}"

	valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./$1 <$file.in >& /dev/null
	exitcode=$?

	if [ $exitcode == 1 ]; then
		exitcode=0;
	fi

	./$1 <$file.in >wyj.out 2>wyj.err

	if diff wyj.out $file.out >& /dev/null && diff wyj.err $file.err >& /dev/null && [ $exitcode == 0 ]; then
		echo -e $i ": \e[32m OK \e[39m"
	else
		if [ $exitcode == 15 ]; then
			echo -e $i ": \e[31m MEM \e[39m"
		else
			echo -e $i ": \e[31m WA \e[39m"
		fi
	fi

	# read -p "Press any key to continue... " -n1 -s
done;

rm wyj.out
rm wyj.err
