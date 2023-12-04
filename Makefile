CC=gcc
FLAGS=-Wall -g -MMD -Iutils

SRC=main.c \
	$(wildcard utils/*.c) \
	$(wildcard 0*/*.c) \
	$(wildcard 1*/*.c) \
	$(wildcard 2*/*.c) \

OBJ=$(addprefix build/obj/,$(addsuffix .o,$(basename $(SRC))))
DEP=$(addprefix build/obj/,$(addsuffix .d,$(basename $(SRC))))

.PHONY: all clean

all: aoc

aoc: $(OBJ)
	@echo "link and compile $@"
	@$(CC) $(FLAGS) -o aoc $(OBJ)

build/obj/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "compile $<"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf build

-include $(DEP)
