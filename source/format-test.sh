#!/usr/bin/env bash

find . -name "*.c" -o -name "*.h" | xargs clang-format -Werror --dry-run

if [[ $? -eq 0 ]]; then
    echo "No warning"
fi
