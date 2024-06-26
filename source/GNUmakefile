SHELL := /usr/bin/bash

source_codes := main.c scene/develop_terminal.c log/logger.c
executable_base_name := warmaShark_Roulette

clang_flag += -I./
clang_flag += -lncurses

default: warmaShark_Roulette.out

warmaShark_Roulette.out: $(source_codes)
	/usr/bin/clang $(source_codes) \
		--output $(executable_base_name).out \
		$(clang_flag)

clear:
	rm -i $(executable_base_name).out
