# I HATE MAKEFILE!!!

SHELL := /usr/bin/bash
CC := /usr/bin/clang

build_type := debug
executable_base_name := warmaShark

source_codes += main.c
source_codes += log/logger.c runtime.c window.c
source_codes += control/dialogue2.c control/selector.c control/trigger.c
source_codes += scene/develop_terminal.c scene/program_info.c scene/shark_roulette.c scene/selector_show.c

clang_flag += --std=c99
clang_flag += -D_POSIX_C_SOURCE=200809L

clang_flag += -I./
clang_flag += -L./
clang_flag += -lncursesw

clang_flag += -Wall -Wextra
# and disable some stuff ( ´･･)ﾉ(._.`)
clang_flag += -Wno-unused-parameter
clang_flag += -Wno-unused-variable
clang_flag += -Wno-unused-but-set-variable
clang_flag += -Wno-unused-const-variable
clang_flag += -Wno-unused-function
clang_flag += -Wno-sign-compare

# for preprocessor
ifeq (${build_type}, debug)
build_version := Develop Build
clang_flag += -O0
clang_flag += -g
# -rdynamic only enabled in Linux(below)
else ifeq (${build_type}, CI)
build_version := CI Workflow
clang_flag += -O0
else
# release version
build_version := Version 2.2, Build 4
clang_flag += -Os
endif

clang_flag += -DBUILD_VERSION_STRING="\"${build_version}\""
git_repo_info := $(shell git describe --abbrev=40 --dirty --tags --always --long)
clang_flag += -DBUILD_GIT_REPO_INFO_STRING="\"${git_repo_info}\""
build_date:= $(shell date --utc --iso-8601=seconds)
clang_flag += -DBUILD_DATE_STRING="\"${build_date}\""

.PHONY += default
.PHONY += clear

default: warmaShark

warmaShark: ${source_codes} GNUmakefile
	${CC} ${source_codes} \
		--output ${executable_base_name} \
		${clang_flag} \
		-rdynamic

# need libncursesw.a in this folder or global lib path
warmaShark-Linux-Static: ${source_codes} GNUmakefile
	${CC} ${source_codes} \
		--output ${executable_base_name}-Linux-Static \
		${clang_flag} \
		--static

# use MinGW-w64 in Linux enviroment
warmaShark-Windows.exe: ${source_codes} GNUmakefile
	/usr/bin/x86_64-w64-mingw32-gcc ${source_codes} \
		--output ${executable_base_name}-Windows.exe \
		${clang_flag} \
		--static \
		-DNCURSES_STATIC

clear:
	rm -i ${executable_base_name}*
