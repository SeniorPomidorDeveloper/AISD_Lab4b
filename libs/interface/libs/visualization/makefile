COMPILLER = gcc

PATH_LIB_FILES = $(ARG)

NAME_FILE = visualization.c

NAME_OBJECT_FILE = visualization

all: assemble_lib

assemble_lib: compile_lib
	ar r $(NAME_OBJECT_FILE).a $(NAME_OBJECT_FILE).o
	rm *.o

compile_lib:
	$(COMPILLER) -c $(PATH_LIB_FILES)$(NAME_FILE) -o $(NAME_OBJECT_FILE).o -fPIC -Wall -Wextra -g