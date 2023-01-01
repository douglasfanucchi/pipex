NAME=libftprintf.a
TESTS=test.out
CC=clang
CC_FLAGS=-Wall -Wextra -Werror -fPIE
INCLUDES= -I ./includes -I libft
LIBFT=./libft/libft.a
SOURCES_FORMATS = get_char_format.c \
		get_decimal_format.c \
		get_hex_lower_format.c \
		get_hex_upper_format.c \
		get_integer_format.c \
		get_percentage_format.c \
		get_pointer_format.c \
		get_str_format.c \
		get_u_decimal_format.c \


SOURCES = ft_printf.c \
		hex_base_converter.c \
		formats_list.c \

OBJECTS = $(SOURCES:.c=.o) $(SOURCES_FORMATS:.c=.o)

all: | libft

$(NAME): $(OBJECTS) $(LIBFT)
	cp $(LIBFT) $(NAME)
	ar -rcs $(NAME) $(OBJECTS)

libft:
	make -C libft/
	make bonus -C libft/
	make $(NAME)

$(OBJECTS): $(addprefix sources/, $(SOURCES)) $(addprefix sources/formats/, $(SOURCES_FORMATS))
	@$(CC) $(INCLUDES) $(CC_FLAGS) -c $(addprefix sources/, $(SOURCES)) $(addprefix sources/formats/, $(SOURCES_FORMATS))

clean:
	rm -f $(OBJECTS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: libft
