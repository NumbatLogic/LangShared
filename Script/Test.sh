#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LANGUAGE=""
PASS_ARGS=()

for arg in "$@"; do
	case "$arg" in
		--CPP) LANGUAGE="CPP" ;;
		--CS) LANGUAGE="CS" ;;
		*) PASS_ARGS+=("$arg") ;;
	esac
done

if [ "$LANGUAGE" = "" ]; then
	LANGUAGE="CPP"
	echo
	echo "*** No language specified; defaulting to CPP"
	echo
fi

source "$SCRIPT_DIR/_runner.sh"

if [ "$LANGUAGE" = "CS" ]; then
	shopt -s nullglob
	dll_files=(Source/ProjectGen/dotnet10/*/bin/Debug/net*/*Test*.dll)
	if [ ${#dll_files[@]} -eq 0 ]; then
		echo "No C# test binaries found in Source/ProjectGen/dotnet10/*/bin/Debug/net*"
		exit 1
	fi
	for dll in "${dll_files[@]}"; do
		dotnet "$dll" "${PASS_ARGS[@]}"
	done
	exit 0
fi

extract_runner_and_args "${PASS_ARGS[@]}"

shopt -s nullglob
for binary in Bin/*Test*; do
	if [ -f "$binary" ] && [ -x "$binary" ]; then
		run_with_runner "$binary" "${RUNNER_ARGS[@]}"
	fi
done