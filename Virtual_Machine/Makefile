COREWAR_NAME = corewar

CC = gcc
FLAGS = -Wall -Wextra -Werror -O3

# Libraries and Includes

COREWAR_LIBRARIES = -lftprintf -L$(FT_PRINTF_DIRECTORY)

COREWAR_INCLUDES = \
	-I$(HEADERS_DIRECTORY)\
	-I$(LIBFT_HEADERS)\
	-I$(FT_PRINTF_HEADERS)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./ft_lftprintf/includes/libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)

FT_PRINTF = $(FT_PRINTF_DIRECTORY)libftprintf.a
FT_PRINTF_DIRECTORY = ./ft_lftprintf/
FT_PRINTF_HEADERS = $(FT_PRINTF_DIRECTORY)includes/

# Headers

HEADERS_DIRECTORY = ./includes/

COREWAR_HEADERS_LIST = \
	op.h\
	corewar.h\
	error.h\

COREWAR_HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(COREWAR_HEADERS_LIST))

# Sources

COREWAR_SOURCES_DIRECTORY = ./srcs/corewar/

COREWAR_SOURCES_LIST =	corewar.c			\
						check_input.c		\
						calculate.c			\
						get_champion.c		\
						print_some.c		\
						init_resourse.c		\
						free_resourse.c		\
						start_war.c			\
						additional.c		\
						read_code.c			\
						read_memory.c		\
						cycles_to_death.c	\
						op_1_4.c			\
						op_5_8.c			\
						op_9_12.c			\
						op_13_16.c			\

COREWAR_SOURCES = $(addprefix $(COREWAR_SOURCES_DIRECTORY), $(COREWAR_SOURCES_LIST))

# Objects

OBJECTS_DIRECTORY = ./objects/

COREWAR_OBJECTS_DIRECTORY = $(OBJECTS_DIRECTORY)corewar/
COREWAR_OBJECTS_LIST = $(patsubst %.c, %.o, $(COREWAR_SOURCES_LIST))
COREWAR_OBJECTS	= $(addprefix $(COREWAR_OBJECTS_DIRECTORY), $(COREWAR_OBJECTS_LIST))

.PHONY: all clean fclean re

# Colors

CREAT = \033[0;32m
IMPORTANT =\033[1;36m
DELETE = \033[0;31m
EOC = \033[0m

all: $(COREWAR_NAME)

$(COREWAR_NAME): $(FT_PRINTF) $(COREWAR_OBJECTS_DIRECTORY) $(COREWAR_OBJECTS)
	@$(CC) $(FLAGS) $(COREWAR_LIBRARIES) $(COREWAR_INCLUDES) $(COREWAR_OBJECTS) -o $(COREWAR_NAME)
	@echo "$(CREAT)objects were created! >>>$(EOC)"
	@echo "$(IMPORTANT)COREWAR was created! >>>$(EOC)"


$(COREWAR_OBJECTS_DIRECTORY):
	@mkdir -p $(COREWAR_OBJECTS_DIRECTORY)
	@echo "$(CREAT)$(COREWAR_OBJECTS_DIRECTORY) was created! >>>$(EOC)"

$(COREWAR_OBJECTS_DIRECTORY)%.o : $(COREWAR_SOURCES_DIRECTORY)%.c $(COREWAR_HEADERS)
	@$(CC) $(FLAGS) -c $(COREWAR_INCLUDES) $< -o $@
	@echo "$(CREAT)>.. please wait ... objects creating..>>$(EOC)"

$(FT_PRINTF):
	@echo "$(CREAT)Creating $(FT_PRINTF) >>>$(EOC)"
	@$(MAKE) -sC $(FT_PRINTF_DIRECTORY)

clean:
	@$(MAKE) -sC $(FT_PRINTF_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(DELETE)>>> $(OBJECTS_DIRECTORY) was deleted ..............   >>>$(EOC)"
	@echo "$(DELETE)>>> object files were deleted ............. >>>$(EOC)"

fclean: clean
	@$(MAKE) -sC $(FT_PRINTF_DIRECTORY) fclean
	@echo "$(DELETE)>>> $(FT_PRINTF) was deleted >>$(EOC)"
	@rm -f $(COREWAR_NAME)
	@echo "$(DELETE)>>> $(COREWAR_NAME) was deleted ................    >>>$(EOC)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
