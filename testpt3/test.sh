#!/bin/bash

for i in tests/*.in; do
	f="${i%.*}"
	time ../release/phone_forward <$f.in >wyj.out 2>wyj.err
	if diff wyj.out $f.out >& /dev/null && diff wyj.err $f.err >& /dev/null; then echo -e $i ": OK"
	else echo -e $i ": dupa";
	fi
done;

rm wyj.out
rm wyj.err
