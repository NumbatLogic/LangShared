#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_NAME="$(basename "$PWD")"
PROJECT_NAME="${PROJECT_NAME#nll-}"
TEST_PROJECT_NAME="${PROJECT_NAME}Test"

CODECRAB_SCRIPT="./CodeCrab.sh"
if [ ! -f "$CODECRAB_SCRIPT" ]; then
	CODECRAB_SCRIPT="$SCRIPT_DIR/CodeCrab.sh"
fi

TRANSPILE_SCRIPT="./Transpile.sh"
if [ ! -f "$TRANSPILE_SCRIPT" ]; then
	TRANSPILE_SCRIPT="$SCRIPT_DIR/Transpile.sh"
fi

BUILD_SCRIPT="./Build.sh"
if [ ! -f "$BUILD_SCRIPT" ]; then
	BUILD_SCRIPT="$SCRIPT_DIR/Build.sh"
fi

if [ ! -f "Source/${PROJECT_NAME}.php" ]; then
	echo "Missing CPP project file: Source/${PROJECT_NAME}.php"
	exit 1
fi

rm -rf Source/ProjectGen
rm -rf Bin
rm -rf Transpiled

if [ -f "Source/LangShared.package-list" ]; then
	rm -rf "$SCRIPT_DIR/../Transpiled"
fi

"$CODECRAB_SCRIPT"
"$TRANSPILE_SCRIPT"

cd Source
	php "${PROJECT_NAME}.php" "linux_gmake"
	php "${PROJECT_NAME}.php" "esp_idf"
	php "${PROJECT_NAME}.php" "dotnet10"
cd ..

"$BUILD_SCRIPT" "$@"