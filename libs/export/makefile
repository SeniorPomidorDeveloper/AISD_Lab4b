COMPILLER = gcc

PATH_LIB_FILES = $(ARG)

NAME_FILE = export.c

NAME_OBJECT_FILE = export

all: compile_other_libs assemble_lib

assemble_lib: compile_lib
	ar r $(NAME_OBJECT_FILE).a $(NAME_OBJECT_FILE).o *.o
	rm *.o

compile_lib:
	$(COMPILLER) -c $(PATH_LIB_FILES)$(NAME_FILE) -o $(NAME_OBJECT_FILE).o -fPIC -Wall -Wextra -g

compile_other_libs:
	make -f $(PATH_LIB_FILES)../tree/makefile ARG=$(PATH_LIB_FILES)../tree/ 'compile_lib'