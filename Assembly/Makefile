headers = $(wildcard ./includes/*.h)
source_manus = $(wildcard ./manus_source/*.c)
source = $(source_manus) test_run.c
objects = $(source:.c=.o)
flags = -Wextra -g

all: test

%.o : %.c $(headers)
	gcc $(flags) -c $< -I ./includes -o $@

test: $(objects) $(headers)
	gcc $(flags) $^ -I ./includes -L ./ft_printf -lftprintf -o run