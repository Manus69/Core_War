cmake_minimum_required(VERSION 3.15)
project(corewar C)

set(CMAKE_C_STANDARD 11)

include_directories(Virtual_Machine/ft_lftprintf/includes)
include_directories(Virtual_Machine/ft_lftprintf/includes/libft)
include_directories(Virtual_Machine/includes)
include_directories("Новая папка/Virtual_Machine/ft_lftprintf/includes")
include_directories("Новая папка/Virtual_Machine/ft_lftprintf/includes/libft")
include_directories("Новая папка/Virtual_Machine/includes")

add_executable(corewar
        Virtual_Machine/ft_lftprintf/includes/libft/ft_atoi.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_atoi_size_t.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_bzero.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_char_in_string.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_countwords.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_cut_space.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_cutstr.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_get_integer.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_isalnum.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_isalpha.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_isascii.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_isdigit.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_isprint.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_isspace.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_itoa.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_itoa_long.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_itoa_mod.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_length.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_lstadd.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_lstdel.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_lstdelone.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_lstiter.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_lstmap.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_lstnew.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_memalloc.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_memccpy.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_memchr.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_memcmp.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_memcpy.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_memdel.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_memmove.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_memset.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_new_integer_list.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_numzero.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_pow.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_print_symbol.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_putchar.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_putchar_fd.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_putchar_mod.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_putendl.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_putendl_fd.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_putnbr.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_putnbr_fd.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_putnbr_mod.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_putstr.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_putstr_fd.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_putstr_mod.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strcat.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strchr.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strclr.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strcmp.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strcpy.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strcpymap.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strdel.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strdup.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strequ.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_striter.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_striteri.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strjoin.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strlcat.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strlen.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strlen_mod.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strmap.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strmapi.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strncat.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strncmp.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strncpy.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strnequ.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strnew.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strnstr.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strrchr.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strsplit.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strstr.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strsub.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_strtrim.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_thebigest_word.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_tolower.c
        Virtual_Machine/ft_lftprintf/includes/libft/ft_toupper.c
        Virtual_Machine/ft_lftprintf/includes/libft/libft.h
        Virtual_Machine/ft_lftprintf/includes/printf.h
        Virtual_Machine/ft_lftprintf/srcs/base_n_p.c
        Virtual_Machine/ft_lftprintf/srcs/bonus_color.c
        Virtual_Machine/ft_lftprintf/srcs/bonus_fd.c
        Virtual_Machine/ft_lftprintf/srcs/bonus_smile.c
        Virtual_Machine/ft_lftprintf/srcs/color_option.c
        Virtual_Machine/ft_lftprintf/srcs/format_checker.c
        Virtual_Machine/ft_lftprintf/srcs/ft_printf.c
        Virtual_Machine/ft_lftprintf/srcs/print_some_wight_aruc.c
        Virtual_Machine/ft_lftprintf/srcs/work_with_errors.c
        Virtual_Machine/ft_lftprintf/srcs/work_with_flags.c
        Virtual_Machine/ft_lftprintf/srcs/work_with_floats.c
        Virtual_Machine/ft_lftprintf/srcs/work_with_form_x.c
        Virtual_Machine/ft_lftprintf/srcs/work_with_format_char_str.c
        Virtual_Machine/ft_lftprintf/srcs/work_with_int.c
        Virtual_Machine/ft_lftprintf/srcs/work_with_o.c
        Virtual_Machine/ft_lftprintf/srcs/work_with_p.c
        Virtual_Machine/ft_lftprintf/srcs/work_with_u.c
        Virtual_Machine/ft_lftprintf/srcs/work_with_uxo_part_one.c
        Virtual_Machine/ft_lftprintf/srcs/work_with_uxo_part_two.c
        Virtual_Machine/ft_lftprintf/srcs/work_with_x_big.c
        Virtual_Machine/includes/corewar.h
        Virtual_Machine/includes/error.h
        Virtual_Machine/includes/op.h
        Virtual_Machine/srcs/corewar/additional.c
        Virtual_Machine/srcs/corewar/calculate.c
        Virtual_Machine/srcs/corewar/check_input.c
        Virtual_Machine/srcs/corewar/corewar.c
        Virtual_Machine/srcs/corewar/cycles_to_death.c
        Virtual_Machine/srcs/corewar/free_resourse.c
        Virtual_Machine/srcs/corewar/get_champion.c
        Virtual_Machine/srcs/corewar/init_resourse.c
        Virtual_Machine/srcs/corewar/op_13_16.c
        Virtual_Machine/srcs/corewar/op_1_4.c
        Virtual_Machine/srcs/corewar/op_5_8.c
        Virtual_Machine/srcs/corewar/op_9_12.c
        Virtual_Machine/srcs/corewar/print_some.c
        Virtual_Machine/srcs/corewar/read_code.c
        Virtual_Machine/srcs/corewar/read_memory.c
        Virtual_Machine/srcs/corewar/start_war.c
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_atoi.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_atoi_size_t.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_bzero.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_char_in_string.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_countwords.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_cut_space.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_cutstr.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_get_integer.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_isalnum.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_isalpha.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_isascii.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_isdigit.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_isprint.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_isspace.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_itoa.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_itoa_long.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_itoa_mod.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_length.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_lstadd.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_lstdel.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_lstdelone.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_lstiter.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_lstmap.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_lstnew.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_memalloc.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_memccpy.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_memchr.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_memcmp.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_memcpy.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_memdel.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_memmove.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_memset.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_new_integer_list.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_numzero.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_pow.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_print_symbol.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_putchar.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_putchar_fd.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_putchar_mod.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_putendl.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_putendl_fd.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_putnbr.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_putnbr_fd.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_putnbr_mod.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_putstr.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_putstr_fd.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_putstr_mod.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strcat.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strchr.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strclr.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strcmp.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strcpy.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strcpymap.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strdel.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strdup.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strequ.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_striter.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_striteri.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strjoin.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strlcat.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strlen.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strlen_mod.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strmap.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strmapi.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strncat.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strncmp.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strncpy.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strnequ.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strnew.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strnstr.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strrchr.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strsplit.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strstr.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strsub.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_strtrim.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_thebigest_word.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_tolower.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/ft_toupper.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/libft/libft.h"
        "Новая папка/Virtual_Machine/ft_lftprintf/includes/printf.h"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/base_n_p.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/bonus_color.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/bonus_fd.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/bonus_smile.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/color_option.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/format_checker.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/ft_printf.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/print_some_wight_aruc.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/work_with_errors.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/work_with_flags.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/work_with_floats.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/work_with_form_x.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/work_with_format_char_str.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/work_with_int.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/work_with_o.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/work_with_p.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/work_with_u.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/work_with_uxo_part_one.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/work_with_uxo_part_two.c"
        "Новая папка/Virtual_Machine/ft_lftprintf/srcs/work_with_x_big.c"
        "Новая папка/Virtual_Machine/includes/corewar.h"
        "Новая папка/Virtual_Machine/includes/error.h"
        "Новая папка/Virtual_Machine/includes/op.h"
        "Новая папка/Virtual_Machine/includes/visual.h"
        "Новая папка/Virtual_Machine/srcs/corewar/additional.c"
        "Новая папка/Virtual_Machine/srcs/corewar/calculate.c"
        "Новая папка/Virtual_Machine/srcs/corewar/check_input.c"
        "Новая папка/Virtual_Machine/srcs/corewar/corewar.c"
        "Новая папка/Virtual_Machine/srcs/corewar/cycles_to_death.c"
        "Новая папка/Virtual_Machine/srcs/corewar/free_resourse.c"
        "Новая папка/Virtual_Machine/srcs/corewar/get_champion.c"
        "Новая папка/Virtual_Machine/srcs/corewar/init_resourse.c"
        "Новая папка/Virtual_Machine/srcs/corewar/op_13_16.c"
        "Новая папка/Virtual_Machine/srcs/corewar/op_1_4.c"
        "Новая папка/Virtual_Machine/srcs/corewar/op_5_8.c"
        "Новая папка/Virtual_Machine/srcs/corewar/op_9_12.c"
        "Новая папка/Virtual_Machine/srcs/corewar/print_some.c"
        "Новая папка/Virtual_Machine/srcs/corewar/read_code.c"
        "Новая папка/Virtual_Machine/srcs/corewar/read_memory.c"
        "Новая папка/Virtual_Machine/srcs/corewar/start_war.c"
        "Новая папка/Virtual_Machine/srcs/corewar/vis_draw.c"
        "Новая папка/Virtual_Machine/srcs/corewar/vis_init.c"
        "Новая папка/Virtual_Machine/srcs/corewar/vis_keys.c"
        "Новая папка/Virtual_Machine/srcs/corewar/vis_put.c"
        "Новая папка/Virtual_Machine/srcs/corewar/vis_start.c")
