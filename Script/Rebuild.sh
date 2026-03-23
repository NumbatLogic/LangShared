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
	local project_dir="$1"
	local csproj_path="$2"
	local assembly_name="$3"
	local output_type="$4"
	shift 4
	local include_patterns=("$@")

	mkdir -p "$project_dir"
	{
		echo "<Project Sdk=\"Microsoft.NET.Sdk\">"
		echo "  <PropertyGroup>"
		echo "    <AssemblyName>${assembly_name}</AssemblyName>"
		echo "    <TargetFramework>net10.0</TargetFramework>"
		echo "    <EnableDefaultCompileItems>false</EnableDefaultCompileItems>"
		echo "    <Nullable>disable</Nullable>"
		echo "    <ImplicitUsings>disable</ImplicitUsings>"
		echo "    <OutputType>${output_type}</OutputType>"
		echo "  </PropertyGroup>"
		echo
		echo "  <ItemGroup>"

		for pattern in "${include_patterns[@]}"; do
			echo "    <Compile Include=\"${pattern}\" />"
		done

		if [ -f "Source/LangShared.package-list" ]; then
			mapfile -t ls_packages < Source/LangShared.package-list
			for pkg in "${ls_packages[@]}"; do
				if [ -z "$pkg" ] || [[ "$pkg" == \#* ]]; then
					continue
				fi
				echo "    <Compile Include=\"${SCRIPT_DIR}/../Source/${pkg}/**/*.cs\" />"
				echo "    <Compile Include=\"${SCRIPT_DIR}/../Transpiled/${pkg}/**/*.cs\" />"
			done
		fi

		### HAXXXX
		if [ "${output_type}" = "Exe" ]; then
			echo "    <Compile Include=\"../../../../Transpiled/NetObject/**/*.cs\" />"
		fi
		echo "  </ItemGroup>"
		echo "</Project>"
	} > "$csproj_path"
}

for source_dir in Source/*; do
	if [ ! -d "$source_dir" ]; then
		continue
	fi

	folder_name="$(basename "$source_dir")"
	project_php="${source_dir}/${folder_name}.php"
	if [ ! -f "$project_php" ]; then
		continue
	fi

	output_type="Library"
	if grep -q "KIND_CONSOLE_APP" "$project_php"; then
		output_type="Exe"
	fi

	generate_csproj \
		"Source/ProjectGen/dotnet/${folder_name}" \
		"Source/ProjectGen/dotnet/${folder_name}/${folder_name}.csproj" \
		"${folder_name}" \
		"${output_type}" \
		"../../../../Transpiled/${folder_name}/**/*.cs"
done




"$SCRIPT_DIR/Build.sh" "$@"