NAME	:= ft_containers
LNAME	:= ft_leaks
FTNAME	:= ft_test
STLNAME	:= stl_test
TMPLNAME:= .leaks

SRC		:= src/main.cpp

INC		:= inc
BIN		:= bin
TEST	:= test

GCC		:= c++
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
			@$(GCC) $(FLAGS) $(SRC) -o $(BIN)/$(NAME) -D TERM
			@printf "%-50.40s\r\n"
			@printf "%-38.38s\r\t$(YELLOW)$(TICK)$(GRN) $(NAME) was compiled!$(END)\n\n"
			@echo "\t$(BLUE)Usage:"
			@echo "\t\t$(BLUE)make test $(END)run tests for comparison ft:: and std:: containers"
			@echo "\t\t$(BLUE)make ft   $(END)show tests results of ft:: containers test"
			@echo "\t\t$(BLUE)make stl  $(END)show tests results of std:: containers test\n"

dir:
			@mkdir -p $(BIN)

leaks:		dir
			@$(GCC) $(FLAGS) $(SRC) -o $(BIN)/$(LNAME)
			@-leaks --atExit -- $(BIN)/$(LNAME) > $(TMPLNAME)
			@echo "$(YELLOW)" && cat $(TMPLNAME) | grep "total leaked bytes" | cut -d ' ' -f 3,4,5,6,7,8,9 && echo ""
			@$(RM) $(TMPLNAME)

test:		dir
			@mkdir -p $(TEST)
			@$(GCC) $(FLAGS) $(SRC) -o $(BIN)/$(FTNAME)
			@$(GCC) $(FLAGS) $(SRC) -o $(BIN)/$(STLNAME) -D STL
			@$(BIN)/$(FTNAME) > $(TEST)/$(FTNAME)
			@$(BIN)/$(STLNAME) > $(TEST)/$(STLNAME)
			@echo "\n\t$(YELLOW)Test results:$(END)\n"
			@printf "$(GRN)\t$(TICK) Test results for ft:: and std:: are identical, test passed$(END)"
			@printf "%-50.40s\r$(RED)" && diff $(TEST)/$(FTNAME) $(TEST)/$(STLNAME)
			@echo "\n"

ft:
			@$(GCC) $(FLAGS) $(SRC) -o $(BIN)/$(FTNAME) -D TERM
			@./$(BIN)/$(FTNAME)

stl:
			@$(GCC) $(FLAGS) $(SRC) -o $(BIN)/$(STLNAME) -D TERM -D STL
			@./$(BIN)/$(STLNAME)

clean:
			@$(RM) $(BIN)
			@$(RM) $(TEST)
			@echo "\t$(GRN)$(TICK) $(NAME) was cleaned!$(END)"

fclean:		clean
			@echo "\t$(GRN)$(TICK) $(NAME) was fcleaned!$(END)"

re:			fclean all

.PHONY:	 	$(NAME) all dir clean fclean re