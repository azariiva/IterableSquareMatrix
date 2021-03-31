
CC = g++
CF = -std=c++14 -g -ftrapv -fsanitize=undefined -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wcast-qual -Wwrite-strings -lm -L.

CPPFILES = $(shell find src -name '*.cpp')
HPPFILES = $(shell find headers -name '*.hpp') \
			$(shell find headers/selectors -name '*.hpp')
TCCFILES = $(shell find templates -name '*.tcc') \
			$(shell find templates/selectors -name '*.tcc')
	
OFILES = $(addprefix obj/, $(CPPFILES:src/%.cpp=%.o))

CPPTESTS =  $(shell find tests -name '*.cpp')

all: obj

obj:
	mkdir -p obj

obj/%.o: src/%.cpp $(HPPFILES)
	@$(CC) $(CF) -I headers -I headers/selectors -I templates -I templates/selectors -c $< -o $@
	@echo "$@ compiled"

object_files: obj $(OFILES)

clean:
	rm -rf obj

fclean: clean
	rm -f $(OUTTESTS)

re: fclean all

.PHONY: all clean fclean re tests object_files
