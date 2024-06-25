source_codes = main.c scene/develop_terminal.c
executable_name = warmaShark_Roulette.out
lib_ld_flags = -lncurses

ALL: warmaShark_Roulette.out

warmaShark_Roulette.out: $(source_codes)
	/usr/bin/clang $(source_codes) \
		--output $(executable_name) \
		$(lib_ld_flags)
