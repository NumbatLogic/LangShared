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
	mapfile -t sPackageArray < "$sPackageList"
	for sPackage in "${sPackageArray[@]}"; do
		if [ -z "$sPackage" ] || [[ "$sPackage" == \#* ]]; then
			continue
		fi
		sArgs+=("-f")
		sArgs+=("$LANG_SHARED_SOURCE/$sPackage")
	done
fi

sPackageList="Source/External.package-list"
if [ -f "$sPackageList" ]; then
	mapfile -t sPackageArray < "$sPackageList"
	for sPackage in "${sPackageArray[@]}"; do
		if [ -z "$sPackage" ] || [[ "$sPackage" == \#* ]]; then
			continue
		fi
		sArgs+=("-f")
		sArgs+=("../${sPackage}/Source")
	done
fi

sArgs+=("$@")

gdb -ex "set confirm off" -ex run -ex backtrace -ex quit --args "$LANG_CLI" "${sArgs[@]}"
