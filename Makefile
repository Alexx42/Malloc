ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


SRCS = $(addprefix sources/, malloc.c memory_block.c debug.c memory_chunk.c union_operations.c)
OBJ = $(SRCS:.c=.o)

NAME = libft_malloc_$(HOSTTYPE).so
PROG = prog

LINK = libft_malloc.so

FLAGS = -Wall -Werror -Wextra -g3 -finline-functions -fPIC

INCLUDES = -I ./includes/

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	@ gcc $(FLAGS)  $(INCLUDES)  -shared -o $(NAME) $(SRCS)
	@ ln -sf $(NAME) $(LINK)

clean:
	@echo  Cleaning objects.. 
	@rm -f $(OBJ)

fclean: clean
	@echo  Removing executable...
	@rm -f $(NAME) $(PROG) && rm -rf *.dSYM && rm -f ._* && rm -f $(LINK)

re: fclean all

run: $(OBJ)
	@ gcc $(FLAGS) $(INCLUDES) $(SRCS) -o $(PROG)
