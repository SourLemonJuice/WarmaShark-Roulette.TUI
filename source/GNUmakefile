SHELL := /usr/bin/bash

source_codes += main.c scene/develop_terminal.c
source_codes += log/logger.c engine/engine_config.c engine/animator.c
executable_base_name := warmaShark

clang_flag += -I./
clang_flag += -lncurses
clang_flag += -O3

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
	rm -i $(executable_base_name).*
