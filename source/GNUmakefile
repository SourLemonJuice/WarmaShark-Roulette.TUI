# I HATE MAKEFILE!!!

SHELL := /usr/bin/bash

build_type := debug
executable_base_name := warmaShark

source_codes += main.c
source_codes += log/logger.c runtime.c
source_codes += dialogue.c control/dialogue2.c control/selector.c control/trigger.c
source_codes += scene/develop_terminal.c scene/program_info.c scene/shark_roulette.c scene/selector_show.c

clang_flag += -std=c99
clang_flag += -D_POSIX_C_SOURCE=200809L
clang_flag += -Wall -Wextra -Werror
# and disable some stuff ( ´･･)ﾉ(._.`)
clang_flag += -Wno-unused-parameter
clang_flag += -Wno-unused-variable
clang_flag += -Wno-unused-but-set-variable
clang_flag += -Wno-unused-const-variable
clang_flag += -Wno-unused-function
clang_flag += -Wno-sign-compare
# for old version clang
clang_flag += -Wno-unknown-warning-option

clang_flag += -I./
clang_flag += -lncursesw

ifeq (${build_type}, debug)
build_version := Develop Build
clang_flag += -O0
clang_flag += -g
clang_flag += -rdynamic
else ifeq (${build_type}, CI)
build_version := CI Workflow
clang_flag += -O0
else
# release info
build_version := Version 1.0, Build 1
clang_flag += -Os
endif

# for preprocessor
clang_flag += -DBUILD_VERSION_STRING="\"${build_version}\""
git_repo_info := $(shell git describe --abbrev=40 --dirty --tags --always --long)
clang_flag += -DBUILD_GIT_REPO_INFO_STRING="\"${git_repo_info}\""
build_date:= $(shell LANG=en_US.UTF-8 date --utc +%c)
clang_flag += -DBUILD_DATE_STRING="\"${build_date}\""

default: warmaShark.out

warmaShark.out: $(source_codes) GNUmakefile
	/usr/bin/clang $(source_codes) \
		--output $(executable_base_name).out \
		$(clang_flag)

# this target needs to run in MSYS2 environment
# and... it's a unstable target
warmaShark.exe: $(source_codes)
	clang $(source_codes) \
		--output $(executable_base_name).exe \
		$(clang_flag)

clear:
	rm -i $(executable_base_name).*
