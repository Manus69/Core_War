#Compiler Options
C_FLAGS =  -Wall -Wextra -Werror
#Filenames
NAME_P := push_swap
P_DIR := push_swap_sr
NAME_C := checker
C_DIR := pw_checker
SRCS_P := main_pusher.c stk_utils.c instructions0.c instructions01.c \
		instructions02.c validation.c init_stack.c chunkee.c another_algo.c \
		revolver.c arger_validator.c another_algo_1.c another_algo_2.c revolver_1.c find_devian.c
SSRCS_P := $(addprefix $(P_DIR)/, $(SRCS_P))
OBJECTS_P := $(SSRCS_P:.c=.o)
SRCS_C := arger_validator.c cmp_for_input.c init_stack.c instructions0.c instructions01.c\
	            instructions02.c main_checker.c stk_utils.c validation.c find_devian.c
SSRCS_C := $(addprefix $(C_DIR)/, $(SRCS_C))
OBJECTS_C := $(SSRCS_C:.c=.o)
INCLUDES := ./headers
HEADER := $(INCLUDES)/push_swap.h

all: $(NAME_P) $(NAME_C)

$(NAME_P): $(OBJECTS_P)	
	gcc -o $(NAME_P) $(OBJECTS_P) -L$(INCLUDES) -lft
$(OBJECTS_P): %.o: %.c $(HEADER)
	gcc $(C_FLAGS) -I $(INCLUDES) -o $@ -c $<

$(NAME_C): $(OBJECTS_C)
	gcc -o $(NAME_C) $(OBJECTS_C) -L$(INCLUDES) -lft
$(OBJECTS_C): %.o: %.c $(HEADER)
	gcc $(C_FLAGS) -I$(INCLUDES)  -o $@ -c $<

clean:
	/bin/rm -f $(OBJECTS_P)
	/bin/rm -f $(OBJECTS_C)
fclean: clean
	/bin/rm -f $(NAME_P)
	/bin/rm -f $(NAME_C)
re: fclean all

