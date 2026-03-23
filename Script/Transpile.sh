#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LANG_CLI="$SCRIPT_DIR/../../Lang/Bin/CLI"
LANG_SHARED_SOURCE="$SCRIPT_DIR/../Source"

if [ ! -x "$LANG_CLI" ]; then
	echo "Missing transpiler binary: $LANG_CLI"
	exit 1
fi

sArgs=("-f" "Source")

sPackageList="Source/LangShared.package-list"
if [ -f "$sPackageList" ]; then
	mapfile -t sPackages < "$sPackageList"
	for sPackage in "${sPackages[@]}"; do
		sArgs+=("-f")
		sArgs+=("$LANG_SHARED_SOURCE/$sPackage")
	done
fi

gdb -ex "set confirm off" -ex run -ex backtrace -ex quit --args "$LANG_CLI" "${sArgs[@]}"
