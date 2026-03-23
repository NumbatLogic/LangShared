#!/bin/bash
set -e

LANGUAGE=""
for arg in "$@"; do
	case "$arg" in
		--CPP) LANGUAGE="CPP" ;;
		--CS) LANGUAGE="CS" ;;
		*)
			echo "Unknown argument: $arg"
			echo "Usage: Build.sh [--CPP|--CS]"
			exit 1
			;;
	esac
done

if [ "$LANGUAGE" = "" ]; then
	LANGUAGE="CPP"
	echo
	echo "*** No language specified; defaulting to CPP"
	echo
fi

if [ "$LANGUAGE" = "CS" ]; then
	shopt -s nullglob
	csproj_files=(Source/ProjectGen/dotnet/*/*.csproj)
	if [ ${#csproj_files[@]} -eq 0 ]; then
		echo "No C# projects found in Source/ProjectGen/dotnet"
		exit 1
	fi
	for csproj in "${csproj_files[@]}"; do
		dotnet build "$csproj"
	done
	exit 0
fi

build="debugx64"
if [ $(uname -m) = "aarch64" ];
then
	build="debuga64"
fi

cd Source/ProjectGen/linux_gmake
make config=${build}