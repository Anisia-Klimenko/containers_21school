NAME	:= ft_containers

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

all:
		@$(GCC) $(FLAGS) $(SRC) -o $(BIN)/$(NAME)
		@echo "\n\t$(GRN) $(TICK) FT_CONTAINERS compiled!$(END)\n"

dir:
		@mkdir -p $(BIN)

fclean:
		@$(RM) $(BIN)
		@echo "\n\t$(RED) $(TICK) cleaned!$(END)\n"

-include dir

.PHONY:	 all fclean