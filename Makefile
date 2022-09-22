NAME	:= ft_containers
LNAME	:= ft_containers_leaks

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
			@echo "\n\t$(GRN) $(TICK) FT_CONTAINERS compiled!$(END)\n"

all:		$(NAME)

dir:
			@mkdir -p $(BIN)

leaks:
			@$(GCC) $(FLAGS) $(SRC) -o $(BIN)/$(LNAME)
			@touch .leaks
			@leaks --atExit -- $(BIN)/$(LNAME) > .leaks
			@export var1
			@var1=$(cat .leaks | grep "total leaked bytes" | awk '{print $3}')
#			ifeq ($var1, 0)
#			@echo "\t$(GRN) $(TICK) no leaks!$(END)\n"
#			else
#			@echo "\t$(RED) $(TICK) leaks!$(END)\n"
#			endif
			if [[ $var1 -eq 0 ]]; \
			then \
				echo "\t$(GRN) $(TICK) no leaks!$(END)\n"; \
			else \
				echo "\t$(RED) $(TICK) leaks!$(END)\n"; \
			fi

clean:
			@$(RM) $(BIN)
			@echo "\n\t$(RED) $(TICK) cleaned!$(END)\n"

fclean:		clean

re:			fclean all

.PHONY:	 	$(NAME) all clean fclean re