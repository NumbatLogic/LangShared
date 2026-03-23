#!/bin/bash

extract_runner_and_args() {
	RUNNER=""
	RUNNER_ARGS=()

	for arg in "$@"; do
		if [ "$arg" = "--valgrind" ]; then
			RUNNER="valgrind"
		else
			RUNNER_ARGS+=("$arg")
		fi
	done

	if [ "$RUNNER" = "" ]; then
		RUNNER="gdb"
		echo
		echo "*** No runner specified; defaulting to gdb"
		echo
	fi
}

run_with_runner() {
	local binary="$1"
	shift

	if [ "$RUNNER" = "valgrind" ]; then
		valgrind --trace-children=yes --track-fds=yes --log-file=valgrind.txt --error-limit=no --leak-check=full --show-possibly-lost=yes --track-origins=yes --show-reachable=yes "$binary" "$@"
		if [ -f "valgrind.txt" ]; then
			echo
			echo "*** valgrind.txt ***"
			echo
			sed -n '1,100p' valgrind.txt
			log_lines="$(wc -l < valgrind.txt)"
			if [ "$log_lines" -gt 100 ]; then
				echo
				echo "*** remaining output is in valgrind.txt ***"
			fi
		fi
	else
		gdb -ex "set confirm off" -ex run -ex backtrace -ex quit --args "$binary" "$@"
	fi
}
