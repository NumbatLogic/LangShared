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

APP_FOLDER="${PASS_ARGS[0]}"
if [[ "$APP_FOLDER" == --* ]]; then
	echo "First argument after language switches must be the Source/ console app folder name, not a flag."
	exit 1
fi
TAIL=("${PASS_ARGS[@]:1}")



if [ "$LANGUAGE" = "CS" ]; then
	dll="Source/ProjectGen/dotnet/${APP_FOLDER}/bin/Debug/net10.0/${APP_FOLDER}.dll"
	if [ ! -f "$dll" ]; then
		echo "C# executable not found: ${dll}"
		echo "Run ./Rebuild.sh --CS or ./Build.sh --CS first."
		exit 1
	fi
	dotnet "$dll" "${TAIL[@]}"
	exit 0
fi

source "$SCRIPT_DIR/_runner.sh"

extract_runner_and_args "${TAIL[@]}"

binary="Bin/${APP_FOLDER}"
if [ ! -f "$binary" ]; then
	echo "C++ executable not found: ${binary}"
	echo "Run ./Build.sh or ./Rebuild.sh first."
	exit 1
fi

run_with_runner "$binary" "${RUNNER_ARGS[@]}"
