COMPILLER = gcc

PATH_LIB_FILES = $(ARG)

NAME_FILE = import.c

NAME_OBJECT_FILE = import

all: compile_other_libs assemble_lib

assemble_lib: compile_lib
	ar r $(NAME_OBJECT_FILE).a $(NAME_OBJECT_FILE).o *.o
	rm *.o

compile_lib:
	$(COMPILLER) -c $(PATH_LIB_FILES)$(NAME_FILE) -o $(NAME_OBJECT_FILE).o -fPIC -Wall -Wextra -g