#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/_runner.sh"
extract_runner_and_args "$@"

shopt -s nullglob
for binary in Bin/*Test*; do
	if [ -f "$binary" ] && [ -x "$binary" ]; then
		run_with_runner "$binary" "${RUNNER_ARGS[@]}"
	fi
done