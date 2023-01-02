NAME=pipex
CC=cc
FILES=pipex paths commands/new_command \
		commands/get_command_args
SRC := $(addsuffix .c, $(FILES))
SRC := $(addprefix sources/, $(SRC))
OBJS := $(addsuffix .o, $(FILES))
OBJS := $(OBJS:commands/%=%)

MANDATORY_FILES = commands/commands validate_args open_files clear_pipex
MANDATORY_SRC := $(addsuffix .c, $(MANDATORY_FILES))
MANDATORY_SRC := $(addprefix sources/, $(MANDATORY_SRC))
MANDATORY_OBJS := $(addsuffix .o, $(MANDATORY_FILES))
MANDATORY_OBJS := $(MANDATORY_OBJS:commands/%=%)

BONUS_FILES := commands/commands_bonus validate_args_bonus \
				open_files_bonus clear_pipex_bonus
BONUS_SRC := $(addsuffix .c, $(BONUS_FILES))
BONUS_SRC := $(addprefix sources/, $(BONUS_SRC))
BONUS_OBJS := $(addsuffix .o, $(BONUS_FILES))
BONUS_OBJS := $(BONUS_OBJS:commands/%=%)

PIPEX_LIB = libpipex.a
PRINTF_PATH=lib/ft_printf
FLAGS=-I includes -I $(PRINTF_PATH)/includes -I $(PRINTF_PATH)/libft\
	  -Wall -Werror -Wextra
LIBS=$(PRINTF_PATH)/libftprintf.a
LIBS_FLAGS=-L./ -lpipex -Llib/ft_printf -lftprintf

all: | printf mandatory
bonus: | printf bonuses

$(NAME): all

mandatory: clean_bonuses
	make $(MANDATORY_OBJS)

bonuses: clean_mandatory
	make $(BONUS_OBJS)

$(PIPEX_LIB): $(OBJS)
	ar -rcs $(PIPEX_LIB) $(OBJS)

$(OBJS): $(SRC) $(LIBS)
	$(CC) $(FLAGS) -c $(SRC)

$(MANDATORY_OBJS): $(MANDATORY_SRC) $(PIPEX_LIB)
	$(CC) $(FLAGS) -c $(MANDATORY_SRC)
	$(CC) $(MANDATORY_OBJS) $(LIBS_FLAGS) -o $(NAME)

$(BONUS_OBJS): $(BONUS_SRC) $(PIPEX_LIB)
	$(CC) $(FLAGS) -c $(BONUS_SRC)
	$(CC) $(BONUS_OBJS) $(LIBS_FLAGS) -o $(NAME)

printf:
	make -C $(PRINTF_PATH)

clean_bonuses:
	rm -rf $(BONUS_OBJS)

clean_mandatory:
	rm -rf $(MANDATORY_OBJS)

clean: clean_mandatory clean_bonuses
	make -C $(PRINTF_PATH)/ clean
	rm -rf $(PIPEX_LIB)
	rm -rf $(OBJS)

fclean: clean
	make -C $(PRINTF_PATH)/ fclean
	rm -rf $(NAME)

re: fclean all
