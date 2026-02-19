#!/usr/bin/env sh
set -eu

ROOT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"

printf "SRCS:=\n" > "$ROOT_DIR/srcs.mk"

find "$ROOT_DIR" -type f -name '*.c' -printf '%P\n' \
  | sort \
  | tail -n +36 \
  > "$ROOT_DIR/srcs"
