headers = $(wildcard ./includes/*.h)
source_manus = $(wildcard ./manus/*.c)
source = $(source_manus) test_run.c
objects = $(source:.c=.o)

all: test

%.o : %.c $(headers)
	gcc -c $< -I./includes -o $@

test: $(objects) $(headers)
	gcc $^ -I ./includes -L ./ft_printf -lftprintf -o test_run