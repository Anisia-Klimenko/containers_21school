NAME	:= ft
LNAME	:= ft_leaks
TMPLNAME:= .leaks

SRC		:= src/main.cpp

INC		:= inc
BIN		:= bin

GCC		:= g++
FLAGS	:= -Wall -Wextra -Werror -std=c++98 -I $(INC)

RM		:= rm -rf

BLUE 	= \033[1;34m
GRN		= \033[1;32m
RED		= \033[0;31m
VIOLET	= \033[0;35m
YELLOW	= \033[1;33m
TICK	= \xE2\x9C\x94
END		= \033[0m

all:		$(NAME)

$(NAME):	dir
			@$(GCC) $(FLAGS) $(SRC) -o $(BIN)/$(NAME)
			@printf "%-50.40s\r\n"
			@printf "%-38.38s\r\t$(YELLOW)$(TICK)$(GRN) $(NAME) was compiled!$(END)\n\n"
			@echo "\t$(BLUE)Usage: make test\n"

dir:
			@mkdir -p $(BIN)

leaks:		dir
			@$(GCC) $(FLAGS) $(SRC) -o $(BIN)/$(LNAME)
			@-leaks --atExit -- $(BIN)/$(LNAME) > $(TMPLNAME)
			@echo "$(YELLOW)" && cat $(TMPLNAME) | grep "total leaked bytes" | cut -d ' ' -f 3,4,5,6,7,8,9 && echo ""
			@$(RM) $(TMPLNAME)

test:		all
			@./bin/ft

clean:
			@$(RM) $(BIN)
			@echo "\t$(GRN)$(TICK) $(NAME) was cleaned!$(END)"

fclean:		clean
			@echo "\t$(GRN)$(TICK) $(NAME) was fcleaned!$(END)"

re:			fclean all

.PHONY:	 	$(NAME) all dir clean fclean re