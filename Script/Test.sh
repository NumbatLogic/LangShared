#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RUNNER="gdb"

if [ "${1:-}" = "--valgrind" ]; then
	RUNNER="valgrind"
fi

shopt -s nullglob

for binary in Bin/*Test*; do
	if [ -f "$binary" ] && [ -x "$binary" ]; then
		if [ "$RUNNER" = "valgrind" ]; then
			valgrind --trace-children=yes --track-fds=yes --log-file=valgrind.txt --error-limit=no --leak-check=full --show-possibly-lost=yes --track-origins=yes --show-reachable=yes "$binary"
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
			gdb -ex "set confirm off" -ex run -ex backtrace -ex quit --args "$binary"
		fi
	fi
done