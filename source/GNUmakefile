SHELL := /usr/bin/bash

source_codes := main.c scene/develop_terminal.c log/logger.c engine/engine_config.c
executable_base_name := warmaShark

clang_flag += -I./
clang_flag += -lncurses
clang_flag += -O3

default: warmaShark.out

warmaShark.out: $(source_codes)
	/usr/bin/clang $(source_codes) \
		--output $(executable_base_name).out \
		$(clang_flag)

clear:
	rm -i $(executable_base_name).out
