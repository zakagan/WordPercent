 #!/bin/bash

return_dir=`pwd`
cd "${0%/*}"

time_stamp=`date +%Y-%m-%d__%H_%M_%S`

extension=".txt"

input_path="../test_files/worst_case/"
input_name="worst_case"
input_prefix=$input_path$input_name

results_path="../test_results/"
mkdir -p $results_path
results_path="${results_path}extended_worst_case"
results_prefix="results_EWC_"
results_suffix="_${time_stamp}${extension}"

executable_path="../"
executables=("WordFormablePartials" "WordFormableTable")

test_quotes="\"\""
test_str="zyxwvutsrqponmlkjihgfedcba9876543210-ZYXWVUTSRQPONMLKJIHGFEDCBA"

EWC_STR_LEN=()
for ((i=25;i<=60;i+=5)); do 
	WC_STR_LEN+=($i)
done

n=0
results_path_attempt="${results_path}${n}/"
while ! mkdir "$results_path_attempt" 2> /dev/null; do
	n=$((n+1))
	results_path_attempt="${results_path}${n}/"
done
results_path=$results_path_attempt

#Header
for executable in ${executables[@]}; do
	results_file=$results_path$results_prefix$executable$results_suffix
	echo "Testing K & M: worst case string lengths"  1> $results_file
	echo "SOLUTION: $executable" 1>> $results_file
	echo ""  1>> $results_file
	echo "string used for testing: $test_str" 1>> $results_file
done

#Tests
for len in ${EWC_STR_LEN[@]}; do
	for executable in ${executables[@]}; do
		results_file=$results_path$results_prefix$executable$results_suffix
		input_file=$input_prefix$len$extension
		if [ $len = 0 ]; then
			current_str=$test_quotes
		else
			current_str=${test_str:0:$len}
		fi
		echo "" 1>> $results_file
		echo "FILE: $input_file" 1>> $results_file
		echo "LENGTH: $len" 1>> $results_file
		echo "$executable_path$executable $current_str $input_file 1" 1>> $results_file
		(time $executable_path$executable $current_str $input_file 1) >> $results_file 2>&1
		for ((j=1;j<=4;j++)); do
			(time $executable_path$executable $current_str $input_file 1) 2>> $results_file 1> /dev/null
		done
	done
done

cd $return_dir