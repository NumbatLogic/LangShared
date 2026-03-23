#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

rm -rf Source/ProjectGen
rm -rf Bin
rm -rf Transpiled

if [ -f "Source/LangShared.package-list" ]; then
	rm -rf "$SCRIPT_DIR/../Transpiled"
fi

"$SCRIPT_DIR/Transpile.sh"

cd Source
	php "NetObject.php" "linux_gmake"
cd ..

# shoudn't need to clean as we wiped out all the directories
#cd Source/ProjectGen/linux_gmake
#make config=${build} clean
#cd ../../..

"$SCRIPT_DIR/Build.sh"