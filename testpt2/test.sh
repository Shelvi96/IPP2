#!/bin/bash

for i in tests/*.in; do
	f="${i%.*}"
	./phone_forward <$f.in >wyj.out 2>wyj.err
	if diff wyj.out $f.out; diff wyj.err $f.err; then echo -e $i ": OK"
	else echo -e $i ": dupa";
	fi
done;

rm wyj.out
rm wyj.err