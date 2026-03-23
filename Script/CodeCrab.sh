#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CODECRAB_PATH="$SCRIPT_DIR/../../CodeCrab/CodeCrab.php"

if [ ! -f "$CODECRAB_PATH" ]; then
	echo "Missing CodeCrab.php: $CODECRAB_PATH"
	exit 1
fi

cd Source
"$SCRIPT_DIR/_php.sh" "$CODECRAB_PATH" "."
