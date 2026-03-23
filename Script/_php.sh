#!/bin/bash
set -e

php \
	-d short_open_tag=true \
	-d log_errors=0 \
	-d display_errors=1 \
	-d display_startup_errors=1 \
	-d error_reporting=E_ALL \
	-d date.timezone=UTC \
	"$@"
