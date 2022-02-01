SRC				= ../src/draw_line.c \
                  	../src/draw.c \
					../src/view_operations.c \
					../src/parsing.c \
					../src/parsing_measure_map.c \
					../src/manipulate_grid.c \
					../src/debug.c \
					../src/matrix.c \
					../src/memory.c \


TEST_HEADERS		= $(shell find ./ -type f -name "*.h")

TEST_SOURCES		= $(shell find ./ -type f -name "*.c")

OBJS				= $(SRC:.c=.o)

MAIN				= test_main.c

NAME				= test_executable.o

CC					= gcc -lbsd -ggdb

RM					= rm -f

ICRITERION			= -L../criterion-v2.3.3/lib -I../criterion-v2.3.3/include -lcriterion -Wl,-rpath=../criterion-v2.3.3/lib

ILIBFT				= -L../lib/libft -lft -I../lib/libft -lft

ISRC				= -I../src

CFLAGS				= -Wall -Wextra -Werror

${NAME}:			$(TARGET_NAME) $(SRC) $(TEST_HEADERS) $(TEST_SOURCES)
					$(MAKE) -C  ../ all
					${CC} -D TESTING ${CFLAGS} -o $(NAME) $(TEST_SOURCES) $(SRC) $(ICRITERION) $(ISRC) $(ILIBFT) -lm

all:				${NAME}

fclean:
					$(MAKE) -C  ../ fclean
					${RM} ${NAME}

re:					fclean all

run: 				all
	@./$(NAME)

.PHONY: clean all re

