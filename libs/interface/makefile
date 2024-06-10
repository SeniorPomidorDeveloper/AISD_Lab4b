COMPILLER = gcc

PATH_LIB_FILES = $(ARG)

NAME_FILE = menu.c

NAME_OBJECT_FILE = menu

all: compile_other_libs assemble_lib

assemble_lib: compile_lib
	ar r $(NAME_OBJECT_FILE).a $(NAME_OBJECT_FILE).o *.o
	rm *.o

compile_lib: compile_main_libs
	$(COMPILLER) -c $(PATH_LIB_FILES)$(NAME_FILE) -o $(NAME_OBJECT_FILE).o -fPIC -Wall -Wextra -g

compile_main_libs:
	make -f $(PATH_LIB_FILES)./libs/gets/makefile ARG=$(PATH_LIB_FILES)libs/gets/ 'compile_lib'
	make -f $(PATH_LIB_FILES)./libs/input/makefile ARG=$(PATH_LIB_FILES)libs/input/ 'compile_lib'
	make -f $(PATH_LIB_FILES)./libs/visualization/makefile ARG=$(PATH_LIB_FILES)libs/visualization/ 'compile_lib'
