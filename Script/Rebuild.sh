#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_NAME="$(basename "$PWD")"
PROJECT_NAME="${PROJECT_NAME#nll-}"
TEST_PROJECT_NAME="${PROJECT_NAME}Test"

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

./CodeCrab.sh
./Transpile.sh

cd Source
	php "${PROJECT_NAME}.php" "linux_gmake"
	php "${PROJECT_NAME}.php" "dotnet10"
cd ..

./Build.sh "$@"