COREWAR_NAME = corewar
ASM_NAME = asm

CC = gcc
FLAGS = -Wall -Wextra -Werror

ASM_LIBRARIES = -lftprintf -L$(FT_PRINTF_DIRECTORY)
COREWAR_LIBRARIES = -lncurses -lftprintf -L$(FT_PRINTF_DIRECTORY)

ASM_INCLUDES = \
	-I$(HEADERS_DIRECTORY)\
	-I$(LIBFT_HEADERS)\
	-I$(FT_PRINTF_HEADERS)

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

HEADERS_DIRECTORY = ./includes/

COREWAR_HEADERS_LIST =		\
	op.h					\
	corewar.h				\
	error.h					\
	visual.h				\

COREWAR_HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(COREWAR_HEADERS_LIST))

ASM_HEADERS_LIST =			\
	asm.h					\
	constants.h				\
	diz_asm.h				\
	function_prototypes.h	\
	generic_list.h			\
	op.h					\
	tables.h					\
	tokens.h				\

ASM_HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(ASM_HEADERS_LIST))

COREWAR_SOURCES_DIRECTORY = ./srcs/corewar/

COREWAR_SOURCES_LIST =	corewar.c					\
						check_input.c				\
						calculate.c					\
						get_champion.c				\
						print_some_1.c				\
						print_some_2.c				\
						init_resourse.c				\
						free_resourse.c				\
						start_war.c					\
						additional.c				\
						read_code.c					\
						read_memory.c				\
						cycles_to_death.c			\
						op_1_4.c					\
						op_5_8.c					\
						op_9_12.c					\
						op_13_16.c					\
						vis_start.c					\
						vis_init.c					\
						vis_keys.c					\
						vis_put.c					\
						vis_draw.c					\
						vis_data.c					\

COREWAR_SOURCES = $(addprefix $(COREWAR_SOURCES_DIRECTORY), $(COREWAR_SOURCES_LIST))

ASM_SOURCES_DIRECTORY = ./srcs/assembler/

ASM_SOURCES_LIST =		asm_main.c 					\
						buffer.c					\
						check.c						\
						classify.c					\
						classify_token.c			\
						classify_token_subroutines.c\
						collect_pre_print_code.c 	\
						complex_instructions.c 		\
						complex_instructions_01.c   \
						container.c					\
						create_file.c				\
						display_stuff.c				\
						display_token.c				\
						distances.c					\
						encode_arguments.c			\
						encode_operations.c			\
						encode_strings.c			\
						encode_type.c				\
						error.c						\
						file_stuff.c				\
						flag_check.c				\
						fork_to_read.c				\
						ft_binary_read.c			\
						generic_list.c				\
						generic_list_part2.c		\
						is_it_fun.c					\
						is_it_good.c				\
						mallokill.c					\
						measure_size.c				\
						open_octo_file.c			\
						print_binary.c				\
						put_name_comment.c			\
						read_file.c					\
						simple_instrutions.c 		\
						support_fluff.c				\
						support_scuff.c				\
						support_snuff.c				\
						support_stuff.c				\
						take_name.c					\
						test_run.c					\
						token.c						\
						token_status.c				\
						transcription.c				\
						translation.c				\
						translation_aggravation.c	\
						translation_frustration.c	\
						translation_vexation.c		\
						validate_dizasm_init.c		\
						walk_throw_byte.c			\
						what_is_it.c				\

ASM_SOURCES = $(addprefix $(ASM_SOURCES_DIRECTORY), $(ASM_SOURCES_LIST))

OBJECTS_DIRECTORY = ./objects/

COREWAR_OBJECTS_DIRECTORY = $(OBJECTS_DIRECTORY)corewar/
COREWAR_OBJECTS_LIST = $(patsubst %.c, %.o, $(COREWAR_SOURCES_LIST))
COREWAR_OBJECTS	= $(addprefix $(COREWAR_OBJECTS_DIRECTORY), $(COREWAR_OBJECTS_LIST))

ASM_OBJECTS_DIRECTORY = $(OBJECTS_DIRECTORY)asm/
ASM_OBJECTS_LIST = $(patsubst %.c, %.o, $(ASM_SOURCES_LIST))
ASM_OBJECTS	= $(addprefix $(ASM_OBJECTS_DIRECTORY), $(ASM_OBJECTS_LIST))

.PHONY: all clean fclean re

CREAT = \033[0;32m
IMPORTANT =\033[1;36m
DELETE = \033[0;31m
EOC = \033[0m

all: $(COREWAR_NAME) $(ASM_NAME)

$(COREWAR_NAME): $(FT_PRINTF) $(COREWAR_OBJECTS_DIRECTORY) $(COREWAR_OBJECTS)
	@$(CC) $(FLAGS) $(COREWAR_INCLUDES) $(COREWAR_OBJECTS) -o $(COREWAR_NAME) $(COREWAR_LIBRARIES)
	@echo "$(CREAT)objects were created! >>>$(EOC)"
	@echo "$(IMPORTANT)COREWAR was created! >>>$(EOC)"

$(ASM_NAME): $(FT_PRINTF) $(ASM_OBJECTS_DIRECTORY) $(ASM_OBJECTS)
	@$(CC) $(FLAGS) $(ASM_INCLUDES) $(ASM_OBJECTS) -o $(ASM_NAME) $(ASM_LIBRARIES)
	@echo "$(CREAT)objects were created! >>>$(EOC)"
	@echo "$(IMPORTANT)ASM was created! >>>$(EOC)"

$(COREWAR_OBJECTS_DIRECTORY):
	@mkdir -p $(COREWAR_OBJECTS_DIRECTORY)
	@echo "$(CREAT)$(COREWAR_OBJECTS_DIRECTORY) was created! >>>$(EOC)"

$(COREWAR_OBJECTS_DIRECTORY)%.o : $(COREWAR_SOURCES_DIRECTORY)%.c $(COREWAR_HEADERS)
	@$(CC) $(FLAGS) -c $(COREWAR_INCLUDES) $< -o $@
	@echo "$(CREAT)>.. please wait ... objects creating..>>$(EOC)"

$(ASM_OBJECTS_DIRECTORY):
	@mkdir -p $(ASM_OBJECTS_DIRECTORY)
	@echo "$(CREAT)$(ASM_OBJECTS_DIRECTORY) was created! >>>$(EOC)"

$(ASM_OBJECTS_DIRECTORY)%.o : $(ASM_SOURCES_DIRECTORY)%.c $(ASM_HEADERS)
	@$(CC) $(FLAGS) -c $(ASM_INCLUDES) $< -o $@
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
	@rm -f $(ASM_NAME)
	@echo "$(DELETE)>>> $(COREWAR_NAME) was deleted ................    >>>$(EOC)"
	@echo "$(DELETE)>>> $(ASM_NAME) was deleted ................    >>>$(EOC)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
