#Compiler Options
C_FLAGS = -Wextra -g
#Filenames
NAME := asm
P_DIR := src_diz
SRCS_P := ft_binary_read.c open_octo_file.c\
   		validate_dizasm_init.c print_binary.c collect_pre_print_code.c put_name_comment.c\
		walk_throw_byte.c complex_instructions.c simple_instrutions.c create_file.c
SRC := asm_main.c fork_to_read.c take_name.c
ASM_DIR := manus_source
SRCS_ASM := test_run.c buffer.c classify.c container.c display_stuff.c distances.c encode_arguments.c encode_operations.c\
		encode_strings.c file_stuff.c generic_list.c mallokill.c support_stuff.c token.c token_status.c\
		transcription.c translation.c what_is_it.c
SSRCS_ASM :=$(addprefix $(ASM_DIR)/, $(SRCS_ASM))
SSRCS_P := $(addprefix $(P_DIR)/, $(SRCS_P))
OBJECTS_P := $(SSRCS_P:.c=.o)
OBJECTS_ASM := $(SSRCS_ASM:.c=.o)
OBJECTS_ROOT := $(SRC:.c=.o)
INCLUDES := ./includes
HEADER := $(INCLUDES)/*.h
PRINTF := libftprintf.a
LIB_PRINT := $(addprefix $(PRINTF_DIR)/, $(PRINTF))
PRINTF_DIR := ft_printf

all: $(LIB_PRINT)  $(NAME)

#
debug_source = debug_stuff.c test_run.c classify.c display_stuff.c distances.c encode_arguments.c encode_operations.c\
		encode_strings.c file_stuff.c generic_list.c mallokill.c support_stuff.c token.c\
		transcription.c translation.c what_is_it.c
debug_source_p = $(addprefix $(ASM_DIR)/, $(debug_source))
debug_objects = $(debug_source_p:.c=.o)

debug: $(debug_objects)
	gcc -o run_debug $(debug_objects) -L$(PRINTF_DIR) -lftprintf

$(debug_objects): %.o: %.c $(HEADER)
	gcc $(C_FLAGS) -I $(INCLUDES) -o $@ -c $<

#

$(NAME): $(OBJECTS_P) $(OBJECTS_ROOT) $(OBJECTS_ASM)
	gcc -o $(NAME) $(OBJECTS_P) $(OBJECTS_ROOT) $(OBJECTS_ASM) -L$(PRINTF_DIR) -lftprintf
$(OBJECTS_P): %.o: %.c $(HEADER)
	gcc $(C_FLAGS) -I $(INCLUDES) -o $@ -c $<
$(OBJECTS_ROOT): %.o: %.c $(HEADER)
	gcc $(C_FLAGS) -I $(INCLUDES) -o $@ -c $<
$(OBJECTS_ASM): %.o: %.c $(HEADER)
	gcc $(C_FLAGS) -I $(INCLUDES) -o $@ -c $<

.FORCE:

$(LIB_PRINT): .FORCE
	make -C $(PRINTF_DIR)

clean:
	/bin/rm -f $(OBJECTS_P)
	/bin/rm -f $(OBJECTS_ASM)
	/bin/rm -f $(OBJECTS_ROOT)
	make fclean -C $(PRINTF_DIR)
fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C $(PRINTF_DIR)
re: fclean all
