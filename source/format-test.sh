#!/usr/bin/env bash

find . -name "*.c" -o -name "*.h" | xargs clang-format -Werror --dry-run

echo "嘛，配置 selector 时有点问题是正常的..."
