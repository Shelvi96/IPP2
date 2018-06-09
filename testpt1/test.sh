valg=true

for i in "empty_struct" "no_forward" "wrong_arguments" "breaking_struct" "long_numbers" "many_numbers" "copy_arguments" "two_structs" "delete_null" "persistent_results" "forward_overwrite" "remove_forward" "simple_reverse" "various_ops" "many_ops" "very_long" "many_remove" "add_remove"; do

		time ./phone_forward $i

	
	code=$?
	
	if [ $code == 0 ]; then
		echo "$i -> OK"
	elif [ $code == 1 ]; then
		echo "$i -> WA"
	elif [ $code == 2 ]; then
		echo "$i -> WRONG_TEST"
	elif [ $code == 15 ]; then
		echo "$i -> MEM_LEAK"
	else
		echo "$i -> JAKIS ERROR"
	fi
done;
