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

"$SCRIPT_DIR/CodeCrab.sh"
"$SCRIPT_DIR/Transpile.sh"

# CPP
cd Source
	php "${PROJECT_NAME}.php" "linux_gmake"
cd ..

# CS
generate_csproj() {
	local sProjectDir="$1"
	local sCsprojPath="$2"
	local sAssemblyName="$3"
	local sOutputType="$4"
	shift 4
	local sIncludePatternArray=("$@")

	mkdir -p "$sProjectDir"
	{
		echo "<Project Sdk=\"Microsoft.NET.Sdk\">"
		echo "  <PropertyGroup>"
		echo "    <AssemblyName>${sAssemblyName}</AssemblyName>"
		echo "    <TargetFramework>net10.0</TargetFramework>"
		echo "    <EnableDefaultCompileItems>false</EnableDefaultCompileItems>"
		echo "    <Nullable>disable</Nullable>"
		echo "    <ImplicitUsings>disable</ImplicitUsings>"
		echo "    <OutputType>${sOutputType}</OutputType>"
		echo "  </PropertyGroup>"
		echo
		echo "  <ItemGroup>"

		for sIncludePattern in "${sIncludePatternArray[@]}"; do
			echo "    <Compile Include=\"${sIncludePattern}\" />"
		done

		if [ -f "Source/LangShared.package-list" ]; then
			mapfile -t sPackageArray < Source/LangShared.package-list
			for sPackage in "${sPackageArray[@]}"; do
				if [ -z "$sPackage" ] || [[ "$sPackage" == \#* ]]; then
					continue
				fi
				echo "    <Compile Include=\"${SCRIPT_DIR}/../Source/${sPackage}/**/*.cs\" />"
				echo "    <Compile Include=\"${SCRIPT_DIR}/../Transpiled/${sPackage}/**/*.cs\" />"
			done
		fi

		if [ -f "Source/External.package-list" ]; then
			mapfile -t sPackageArray < Source/External.package-list
			for sPackage in "${sPackageArray[@]}"; do
				if [ -z "$sPackage" ] || [[ "$sPackage" == \#* ]]; then
					continue
				fi
				echo "    <Compile Include=\"../../../../../${sPackage}/Transpiled/**/*.cs\" />"
				echo "    <Compile Include=\"../../../../../${sPackage}/Source/CS/*.cs\" />"
			done
		fi

		echo "  </ItemGroup>"

		# HAXXXXXXX
		if [ -f "Source/External.package-list" ] && grep -q "^nll-PgSql$" "Source/External.package-list"; then
			echo
			echo "  <ItemGroup>"
			echo "    <PackageReference Include=\"Npgsql\" Version=\"10.0.2\" />"
			echo "  </ItemGroup>"
		fi

		echo "</Project>"
	} > "$sCsprojPath"
}

sLibraryFolderArray=()
sExeFolderArray=()
for sSourceDir in Source/*; do
	if [ ! -d "$sSourceDir" ]; then
		continue
	fi

	sFolderName="$(basename "$sSourceDir")"
	sProjectPhp="${sSourceDir}/${sFolderName}.php"
	if [ ! -f "$sProjectPhp" ]; then
		continue
	fi

	if grep -q "KIND_CONSOLE_APP" "$sProjectPhp"; then
		sExeFolderArray+=("$sFolderName")
	else
		sLibraryFolderArray+=("$sFolderName")
	fi
done

for sFolderName in "${sExeFolderArray[@]}"; do
	sIncludePatternArray=("../../../../Transpiled/${sFolderName}/**/*.cs")
	
	# HAXXXX without real dependancy stuff, just throw every library in
	for sLibraryFolder in "${sLibraryFolderArray[@]}"; do
		sIncludePatternArray+=("../../../../Transpiled/${sLibraryFolder}/**/*.cs")
	done

	generate_csproj \
		"Source/ProjectGen/dotnet/${sFolderName}" \
		"Source/ProjectGen/dotnet/${sFolderName}/${sFolderName}.csproj" \
		"${sFolderName}" \
		"Exe" \
		"${sIncludePatternArray[@]}"
done




"$SCRIPT_DIR/Build.sh" "$@"