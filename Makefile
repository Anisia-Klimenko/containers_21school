NAME	:= ft
LNAME	:= ft_leaks
TMPLNAME:= .leaks

SRC		:= src/main.cpp

INC		:= inc

BIN		:= bin

GCC		:= g++
FLAGS	:= -Wall -Wextra -Werror -std=c++98 -I $(INC)

RM		:= rm -rf

GRN  	:= \033[0;32m
RED  	:= \033[0;31m
YEL  	:= \033[1;33m
END  	:= \033[0m
TICK 	:= \xE2\x9C\x94

$(NAME):	dir
			@$(GCC) $(FLAGS) $(SRC) -o $(BIN)/$(NAME)
			@echo "\n\t$(GRN) $(TICK) FT compiled!$(END)\n"

all:		$(NAME)

dir:
			@mkdir -p $(BIN)

leaks:		dir
			@$(GCC) $(FLAGS) $(SRC) -o $(BIN)/$(LNAME)
			@-leaks --atExit -- $(BIN)/$(LNAME) > $(TMPLNAME)
			@echo "$(YEL)" && cat $(TMPLNAME) | grep "total leaked bytes" | cut -d ' ' -f 3,4,5,6,7,8,9 && echo ""
			@$(RM) $(TMPLNAME)

#LEAKS = $(shell leaks --atExit -- $(BIN)/$(LNAME) ; echo $$?)
#LEAKS = $(shell cat .leaks; echo $$?)
#leaks:		LEAK_MSG = $(if $(filter $(LEAKS), 0), "\n\t$(GRN) $(TICK) ok!\n", "\n\tleaks!\n")
#leaks:
#			@echo $(LEAK_MSG)

clean:
			@$(RM) $(BIN)
			@echo "\n\t$(RED) $(TICK) cleaned!$(END)\n"

fclean:		clean

re:			fclean all

.PHONY:	 	$(NAME) all dir clean fclean re