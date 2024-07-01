SHELL := /usr/bin/bash

test_path := ./
source_path := ../source/

unity_source += ./unity/src/unity.c
include_flag += -I../source/

default: build

build: runtime_test.out

run:
	./runtime_test.out

runtime_test.out: ${unity_source} ${test_path}/runtime.c ${source_path}/runtime.c
	/usr/bin/clang ${unity_source} ${test_path}/runtime.c ${source_path}/runtime.c \
		--output runtime_test.out \
		${include_flag}

clear:
	rm -i *_test.out
