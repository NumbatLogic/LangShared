#!/bin/bash
set -e

build="debugx64"
if [ $(uname -m) = "aarch64" ];
then
	build="debuga64"
fi

cd Source/ProjectGen/linux_gmake
make config=${build}