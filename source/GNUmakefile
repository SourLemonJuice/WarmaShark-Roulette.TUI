# I HATE MAKEFILE!!!

SHELL := /usr/bin/bash

build_type := debug

source_codes += main.c
source_codes += log/logger.c runtime.c dialogue.c control/dialogue2.c control/selector.c control/trigger.c
source_codes += scene/develop_terminal.c scene/program_info.c scene/shark_roulette.c scene/selector_show.c

executable_base_name := warmaShark

clang_flag += -I./
clang_flag += -lncurses
clang_flag += -O0
clang_flag += -rdynamic

ifeq (${build_type}, debug)
clang_flag += -g
endif

# for preprocessor
git_repo_info := $(shell git describe --abbrev=40 --dirty --tags --always --long)
clang_flag += -DBUILD_GIT_REPO_INFO_STRING="\"${git_repo_info}\""
build_date:= $(shell LANG=en_US.UTF-8 date --utc +%c)
clang_flag += -DBUILD_DATE_STRING="\"${build_date}\""

default: warmaShark.out

warmaShark.out: $(source_codes)
	/usr/bin/clang $(source_codes) \
		--output $(executable_base_name).out \
		$(clang_flag)

# this target needs to run in MSYS2 environment
# and... it's a unstable target
warmaShark.exe: $(source_codes)
	/ucrt64/bin/clang.exe $(source_codes) \
		--output $(executable_base_name).exe \
		$(clang_flag)

clear:
	rm -i $(executable_base_name).* *.o
