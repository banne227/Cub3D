#!/usr/bin/env sh
set -eu

ROOT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"

# Generate srcs.mk with proper format
{
	printf "SRCS = "
	find "$ROOT_DIR" -type f -name '*.c' -printf '%P\n' \
		| sort \
		| sed 's/^//' \
		| awk 'NR>1 {printf "\t%s \\\n", prev} {prev=$0} END {printf "%s\n", prev}'
} > "$ROOT_DIR/srcs.mk"
